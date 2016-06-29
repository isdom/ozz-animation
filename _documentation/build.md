---
title: Build
layout: full
keywords: build,cmake,gcc,clang,msvc,emscripten,opengl,glfw,opengl,directx,unit-tests,package
---

{% include references.jekyll %}

Building ozz librairies, tools and samples
==========================================
The build process relies on [cmake](http://www.cmake.org) which allows to propose a portable build system. It is setup to build ozz-animation libraries, tools and samples (along with their data), but also to run unit-tests and package sources/binary distributions. See [the feature-map page][link_features_map] for a list of supported OS and compilers.

You can run CMake as usual from ozz-animation root directory. It is recommended to build out-of-source though (creating "build" directory and running CMake from there):

{% highlight bash %}
mkdir build
cd build
cmake ..
cmake --build ./ --config Release
{% endhighlight %}

An optional python script `build-helper.py` is available in the root directory to help performing all operations:

- Build from sources.
- Run unit-tests.
- Package sources and binaries.
- Configure CMake.
- Clean build directory.
- ...

![](http://my.cdash.org/images/cdash.gif "Title") The nightly [build dashboard][link_dashboard] (based on CDash) allows to monitor most (main, release, develop, features...) branches build status for supported OS.

Integrating ozz in your project
===============================
To use ozz-animation in an application, you'll need to add ozz `include/` path to your project's header search path so that your compiler can include ozz files (paths starting with `ozz/...`).
Then you'll have to setup the project to link with ozz libraries:

- `ozz_base`: Required for any other library. Integrates io, math...
- `ozz_animation`: Integrates all animation runtime jobs, sampling, blending...
- `ozz_animation_offline`: Integrates ozz offline libraries, animation builder, optimizer...
- `ozz_geometry`: Integrates mesh/geometry runtime jobs, skinning...

Some other libraries can also be found for tools, Collada and Fbx... Pre-built libraries, tools and samples can be found on the [download][link_downloads] section.

Integrating ozz sources in your build process
=============================================
Offline and runtime sources can also be integrated to your own build process. ozz does not rely on any configuration file, so you'll only need to add sources files to your build system and add ozz `include/` path as an include directory. It should be straightforward and compatible with all modern c++ compilers.

This solution is interesting for ozz runtime features as it ensures compilers compatibility and allows to trace into ozz code. It works for offline libraries as well.
Integrating Collada or Fbx sources will require to also add their dependencies.