# YoYo QuickStart

<i>
	YoYo QuickStart is a basic graphics template for the YoYo Renderer https://github.com/MokaHiko/YoYo.git
</i>

### Getting Started

<ol>

<li>
<u><b>
Download the repo 
</b></u>
</li>

git clone --recursive https://github.com/MokaHiko/YoYoQuickStart.git.

If the repository was cloned non-recursively previously, use git submodule update --init to clone the necessary submodules.

Supported Platforms: 

 <img height="32" width="32" src="https://raw.githubusercontent.com/github/explore/379d49236d826364be968345e0a085d044108cff/topics/windows/windows.png" /> | <img height="32" width="32" src="https://raw.githubusercontent.com/github/explore/868696fc547869eb5de5add3b3695abdd43bb9dc/topics/macos/macos.png" />  |


<li>
<u><b>
Configuration 
</b></u>
</li>

Run configure.bat or build manual build using cmake -S ./ -B ./build

* <u><i>VULKAN_SDK</i></u> - must be part of your path as an environment variable

<li>
<u><b>
Updating the Renderer
</b></u>
</li>

To update your project to the latest version of YoYo you can use the following command on the root folder of your project

```
	git submodule update YoYo
```
</ol>

### Features 

<center>
	<img src="demo_gifs/mesh_demo.gif">
	<h4>Mesh Rendering</h4>
	example project : https://github.com/MokaHiko/YoYo.git
</center>