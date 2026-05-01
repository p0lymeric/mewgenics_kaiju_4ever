## Kaiju 4Ever

![preview](preview.png)

## Use

Makes it so that the kaiju you've picked in your save remains in the background of the house, even after unlocking the Rift!

This mod only affects rendering logic, and should have no permanent effects on a save.

If the dll file is renamed from `kaiju_4ever.dll` to `kaiju_never.dll`, this mod will instead prevent kaiju from appearing behind the house. However, if you do this, you'll be as evil as a Team Rocket grunt!

## Installation requirements

This mod is packaged for the [Mewtator](https://www.nexusmods.com/mewgenics/mods/1) mod loader and [Mewjector](https://www.nexusmods.com/mewgenics/mods/218) dll loader.

Both are highly recommended for a standard install.

If you encounter crashes or cannot trigger item shuffling, please verify:
* the version of Mewgenics you have installed matches the required version specified in this mod's release notes.
* you have the latest versions of [Mewtator](https://www.nexusmods.com/mewgenics/mods/1) and [Mewjector](https://www.nexusmods.com/mewgenics/mods/218) installed.
* you have dll mod support enabled in Mewtator.

Note that since the Mewgenics dll modding scene is still in its infancy, and because the developers have active plans to release fixes and new content, this mod will likely break in the future with each game update.

## Build requirements

This repository is self-contained, apart from tooling (all C/C++ source code, including that of dependencies, is included).

To compile the dll from source, [CMake](https://cmake.org/) and a contemporary version of the [MSVC compiler (2022/2026)](https://visualstudio.microsoft.com/downloads/) are required.

Developers may appreciate that this dll can be injected standalone with the tool provided under `cpp/cosmic_ooze`, or another tool such as Cheat Engine or System Informer. Players should use Mewjector.

## Licensing

Credits to JamJuice in the Mewgenics modding discord for the idea!

All original material outside of `third_party` directories are distributed under the MIT license. See [LICENSE.md](LICENSE.md) for details.

See [ATTRIBUTION.md](ATTRIBUTION.md) and license documents under `third_party` directories for dependency licenses.
