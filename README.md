# gmsv_stripper
Stripper:Source for Garry's Mod

Based on original [stripper-source][1] and [gm_stripper_lib][2].

Awfully integrates Stripper:Source into Garry's Mod with the help of [garrysmod_common][3] for extra definitions.

Libraries and .vdf files by default should be putted in garrysmod/addons/ folder, you can change a directory, but you'll need to update .vdf files.

This plugin **wont work in singleplayer**, because, as far as i know, server plugins can't be loaded there.

Has an optional FIX_MISSING_KEYS, which you can define to fix 2 entity keys, see [parser.cpp][4]. **Disabled by default**

### Commands

`stripper_status` - Checks stripper status and prints out all applied files. Flags - FCVAR_SERVER_CAN_EXECUTE

## Compiling

The only supported compilation platform for this project on Windows is **Visual Studio 2017** on **release** mode. However, it's possible it'll work with *Visual Studio 2015* and *Visual Studio 2019* because of the unified runtime.

On Linux, everything should work fine as is, on **release** mode.

For macOS, any **Xcode (using the GCC compiler)** version *MIGHT* work as long as the **Mac OSX 10.7 SDK** is used, on **release** mode.

These restrictions are not random; they exist because of ABI compatibility reasons.

If stuff starts erroring or fails to work, be sure to check the correct line endings (\n and such) are present in the files for each OS.

## Requirements

This project requires [garrysmod_common][3], a framework to facilitate the creation of compilations files (Visual Studio, make, XCode, etc). Simply set the environment variable '**GARRYSMOD\_COMMON**' or the premake option '**gmcommon**' to the path of your local copy of [garrysmod_common][3].

We also use [SourceSDK2013][5]. The links to [SourceSDK2013][5] point to [Danielga's](https://github.com/danielga) fork of VALVe's repo and for good reason: Garry's Mod has lots of backwards incompatible changes to interfaces and it's much smaller.

  [1]: https://github.com/alliedmodders/stripper-source
  [2]: https://github.com/Bagellll/gm_stripper_lib
  [3]: https://github.com/danielga/garrysmod_common
  [4]: https://github.com/grylist/stripper-source-gmod/blob/7ab2a0d4282ae01e4d081c88acea33b97a26b69d/source/parser.cpp#L543
  [5]: https://github.com/danielga/sourcesdk-minimal

