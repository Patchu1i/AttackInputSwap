# Attack Input Swap

## What this is:

An SKSE plugin that swaps your Left / Right hand controls when attacking. Requested for accessibility reasons.

By default, your "Left Hand" keybind swings your Right Hand, and your "Right Hand" keybind swings your Left Hand. This is kind of weird. This plugin offers two solutions. You can download the "ALL" version which will swap these for all attack inputs (One Handed, Dual Wield, Spell, Bow, Crossbow, etc). Or you can select the "TWO HAND" version which will only change behaviors for Bows, Crossbows, and Two Handed Weapons.

## Build Requirements

- Any terminal of your choice (e.g., PowerShell)
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [CMake](https://cmake.org/)
  - Edit the `PATH` environment variable and add the cmake.exe install path as a new value
  - Instructions for finding and editing the `PATH` environment variable can be found [here](https://www.java.com/en/download/help/path.html)
- [Git](https://git-scm.com/downloads)
  - Edit the `PATH` environment variable and add the Git.exe install path as a new value
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Install vcpkg using the directions in vcpkg's [Quick Start Guide](https://github.com/microsoft/vcpkg#quick-start-windows)
  - After install, add a new environment variable named `VCPKG_ROOT` with the value as the path to the folder containing vcpkg

## Clone and Build
### Debug
- Clone this repository
- Open project in Visual Studio Code (or Studio)
- Run CMAKE configuration "ATTACK_INPUT_SWITCH_ALL" or "ATTACK_INPUT_SWITCH_TWOHANDED"
- Build
### Release
- Clone this repository
- Run `.\BuildRelease.bat` from VS 2022 Native Command Prompt

(note): The git submodule should automatically init and update recursively on CMake update. If it fails, you'll have to do it manually.

## Attributions
[alandtse - CommonLib NG Fork](https://github.com/alandtse/CommonLibVR/tree/ng)
[meh321 - Address Library](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
[jarari - One Click Power Attack](https://github.com/jarari/OneClickPowerAttack)
[mrowrpurr - Learning & Resources](https://mrowrpurr.com/)


