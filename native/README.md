# Arctic Fluid PS5 Native — 0.2.0 interface prototype

Original native application and software renderer for RicardoStonePT. This application does not reuse the Web File Manager application or start a web server. It presents a 1920x1080 software framebuffer directly through PS5 VideoOut and reads DualSense buttons through ScePad. The sidebar asset is reused from our Windows Arctic interface.

Load arctic-fluid-native-ps5.elf with Payloads Manager. The interface should appear directly on the television. Real hardware behavior on firmware 13.60 has not yet been tested.

Controls: D-pad up/down selects pages on the sidebar; right or cross enters page controls; left/circle returns. L1/R1 cycles pages. Cross opens the PKG or destination picker. In the picker, circle goes to the parent directory, L1 cancels, and Options selects the current destination directory. Options outside the picker opens an exit confirmation, cross confirms, circle cancels.

Implemented: native drawing, sidebar, four pages, theme/language selection, saving settings, read-only PKG/directory selection, and controller navigation. Extraction and installation engines are not integrated in this interface prototype. Their controls report unavailability and do not modify packages. This is not the functional equivalent of the Windows extraction app yet.

Startup diagnostics: /data/arctic_native/startup.log. Settings: /data/arctic_native/settings.txt. If no screen appears, send that log; it records the error code of each display initialization step. A compiled ELF is not proof that VideoOut works on this console/loader combination.

Build: PS5 Payload SDK v0.44, Clang/LLVM/lld, Python. Set PS5_PAYLOAD_SDK and LLVM_CONFIG, then run make. The reproducible GitHub workflow builds the ELF, validates its segments and entry, runs the UI on a Linux host, and packages the corresponding source.

Application source copyright RicardoStonePT, 2026. Video tiling uses a scalar adaptation of the public SDL PS5 addressing formula (zlib license); the interface itself is original. PNG decoding is stb_image, not another application. Font raster data is generated from DejaVu Sans Mono and retains its font license. See THIRD_PARTY_NOTICES.md and FONT_LICENSE.txt.
