
## Description

The **d3d4linux** project allows to compile HLSL shaders on Linux using
the Microsoft DirectX compiler DLL. It works by launching a Windows
program in the background using [Wine](https://www.winehq.org/) and
diverting calls to that server on the fly.

Only four functions are implemented for now. They are the ones
required by the Unreal Engine shader compiler:

  * `D3DCompile`
  * `D3DReflect`
  * `D3DStripShader`
  * `D3DDisassemble`

**d3d4linux** is **work in progress** and **not ready for production**
but is being successfully used at [Dontnod Entertainment](http://dont-nod.com/)
to package Windows versions of Unreal Engine 4 games.

## Build

Prerequisites:

    apt install g++-mingw-w64

Build d3d4linux:

    make

## Test

Prerequisites:

    apt install wine64

Launch the test:

    make check

## Unreal Engine integration

Patch and build:

  * copy the d3d4linux project to `Engine/Sources/ThirdParty/d3d4linux`.
  * apply the patch found in `extras/patch-ue4.11-support.diff` to the Unreal source tree.
  * verify and optionally tweak the `D3D4LINUX_` macros in
    `Engine/Source/Developer/Windows/ShaderFormatD3D/Private/D3D11ShaderCompiler.cpp`
    so that they match your desired setup (note that these can also be overridden at
    runtime using the similarly named environment variables)
  * make sure to rebuild `UE4Editor` and `ShaderCompileWorker`.

Run:

  * with AutomationTool: run `BuildCookRun` as usual with the `-targetplatform=Win64` argument.
  * with UE4Editor: run with the `-run=Cook -TargetPlatform=WindowsNoEditor` arguments.

Debug:

  * set the `D3D4LINUX_VERBOSE` environment variable to `1` for some debugging information.

