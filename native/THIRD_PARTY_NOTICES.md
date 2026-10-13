# Credits and third-party licenses

Own application, UI rendering, navigation and asset integration: RicardoStonePT, 2026.

## SDL PS5 pixel addressing

The function tile_offset and its usage are an altered scalar adaptation of SDL_ps5tilemap.c by John Tornblom, 2026. Upstream: https://github.com/ps5-payload-dev/SDL, commit ee4c47dc0d617b3bc8f35108f9956baf228a1322. This is not the original SDL implementation and does not incorporate the SDL application/UI framework.

Copyright (C) 2026 John Tornblom.
This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

Public PS5 API/ABI references: John Tornblom's ps5-payload-hbldr test.c and ps5-payload-dev/SDL; controller layout cross-checked against br1cks4t1ts/ps5-moonlight. No program UI or file management code from those applications is included.

## stb_image

Sean Barrett and contributors. Dual public-domain/MIT terms are preserved at the end of vendor/stb_image.h. The unchanged decoder is embedded to read our sidebar PNG.

## DejaVu Sans Mono

The bitmap font is generated from DejaVu Sans Mono. The complete installed font attribution/license is in FONT_LICENSE.txt.

## PS5 Payload SDK

Toolchain: https://github.com/ps5-payload-dev/sdk (v0.44). It provides the open-source payload runtime and generated import stubs. Its source and GPL notices are included in the corresponding-source archive. Proprietary console modules are not included; imports resolve to modules already on the PS5.
