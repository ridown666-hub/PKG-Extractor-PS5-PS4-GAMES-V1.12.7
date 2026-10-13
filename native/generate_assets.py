from pathlib import Path
with Path('src/assets.c').open('w') as out:
 for name,file in [('sidebar','assets/sidebar.png'),('font','assets/font.bin')]:
  data=Path(file).read_bytes()
  out.write(f'const unsigned int {name}_size = {len(data)};\nconst unsigned char {name}_data[] = {{\n')
  for i in range(0,len(data),32):out.write(','.join(str(b) for b in data[i:i+32])+',\n')
  out.write('};\n')
