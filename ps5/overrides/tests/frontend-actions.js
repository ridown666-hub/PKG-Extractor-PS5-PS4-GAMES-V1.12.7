// Run: node tests/frontend-actions.js (no browser or dependencies required).
const assert = require('assert');
const fs = require('fs');
const vm = require('vm');
const source = fs.readFileSync(require('path').join(__dirname, '../assets/main.js'), 'utf8');
const context = vm.createContext({});
function load(start, end) {
  vm.runInContext(source.slice(source.indexOf(start), source.indexOf(end)), context);
}
load('async function readDroppedDirectory', 'function actionUploadFiles');
load('function isElfFile', 'function isSupportedArchive');
load('function launchElf', 'function openImagePreview');
context.uploadRelativeName = file => file.webkitRelativePath || file.name;
context.uploadFiles = async (files, paths) => {
  context.result = { names: Array.from(files, file => file.name), paths: Array.from(paths) };
};
const file = name => ({ isFile: true, file: ok => ok({ name, size: 1 }) });
const directory = (name, batches) => ({ name, isDirectory: true,
  createReader() { let index = 0; return { readEntries: ok => ok(batches[index++] || []) }; }
});
async function main() {
  // Multiple readEntries batches and nested directories must retain their paths.
  const root = directory('root', [[file('a')], [directory('sub', [[file('b')]])]]);
  const items = [root, file('c')].map(entry => ({ kind: 'file', webkitGetAsEntry: () => entry }));
  const pending = context.uploadDroppedItems({ items, files: [] });
  items.length = 0; // DataTransfer is only readable synchronously during drop.
  await pending;
  assert.deepStrictEqual(context.result.paths, ['root/a', 'root/sub/b', 'c']);
  await context.uploadDroppedItems({ files: [{ name: 'a' }, { name: 'b' }] });
  assert.deepStrictEqual(context.result.paths, ['a', 'b']);
  await context.uploadDroppedItems({ items: [{ kind: 'file', getAsFile: () => ({ name: 'fallback' }) }] });
  assert.deepStrictEqual(context.result.paths, ['fallback']);
  const error = new Error('read failed');
  await assert.rejects(context.readDroppedDirectory({ createReader: () => ({
    readEntries: (ok, fail) => fail(error)
  }) }), /read failed/);
  assert(context.isElfFile({ type: '-', name: 'payload.ELF' }));
  assert(!context.isElfFile({ type: 'd', name: 'payload.elf' }));
  let sends = 0;
  context.t = key => key;
  context.displayName = item => item.name;
  context.runImmediateAction = (label, fn) => fn();
  context.apiForm = (url, body) => {
    assert.strictEqual(url, '/api/launch-elf');
    assert.strictEqual(body.path, '/payload.elf');
    sends++;
  };
  const payload = { name: 'payload.elf', path: '/payload.elf' };
  context.confirm = () => false;
  context.launchElf(payload);
  assert.strictEqual(sends, 0);
  context.confirm = () => true;
  context.launchElf(payload);
  assert.strictEqual(sends, 1);
  console.log('Frontend actions OK');
}
main().catch(error => { console.error(error); process.exitCode = 1; });
