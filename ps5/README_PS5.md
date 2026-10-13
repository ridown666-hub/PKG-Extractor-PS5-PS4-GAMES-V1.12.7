# Arctic Fluid PS5 — 0.1.0 beta

Adaptation by RicardoStonePT of owendswang's PS5 Web File Manager v1.10.

This is an experimental PS5 ELF with an Arctic interface, file copy/move, PKG preview and the upstream PKG installation request. Full PS4/PS5 PKG extraction to a folder is NOT implemented. Archive extraction requires the upstream wfm-7zip-helper.elf at /data/wfm/wfm-7zip-helper.elf; archives are distinct from PKG containers.

Load arctic-fluid-ps5.elf with Payloads Manager. The startup notification shows the port, starting at 8890. Open http://CONSOLE_IP:8890/ from another device or use the Media shortcut installed by the upstream launcher mechanism. A separate title ID ARCT88889 prevents replacing Web File Manager's FMGR88888 shortcut. The launcher is a browser shortcut, not a native rendered game application.

The installation button submits a request to the system installer and retains the upstream confirmation. A successful submission is not proof that a package finished installing or can launch. Firmware 13.60 and actual package compatibility must be tested on the console. No firmware offsets or kernel patches were added.

The modified source is under ps5/overrides. The workflow fetches upstream commit 3368c82cb50f41e19de80d4fcfffeb05e47b8eb7, initializes its pinned submodule, applies these files, and builds with PS5 Payload SDK v0.44. The distribution includes complete source and the licenses of its dependencies. GPLv3-or-later applies to the adaptation, as with the upstream project. Preserve all upstream credits and LGPL obligations for libsmb2/libmicrohttpd.

Validation: JavaScript syntax and upstream frontend actions tests passed. ELF build and header verification are performed in GitHub Actions. Runtime behavior on PS5 remains unverified.

Next work: a native PKG extraction backend and validation using known test packages. The supplied Windows extraction backend is .NET and cannot run unchanged on PS5. The public C++ LibProsperoPKG rewrite currently describes itself as incomplete, so it is not treated as a working extraction backend.
