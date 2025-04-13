# Princess VS Tools
Princess is a free, open-source, and cross-platform visual scripting tool built with modern C++ 20 licensed under the permissive MIT License. 

Currently you can target Windows, macOS and Linux. Princess may work on UNIX systems, but support isn't guaranteed.

>[!WARNING]
>Princess is still in early alpha and extensive testing is still required. Work is being done to add features constantly, and the API is subject to breaking changes at any moment while work is being done to get Princess to a complete 1.0 release.

## Documentation

Docs are still a work in progress, but expect them to be here by the time Princess 1.0 is released.

## Features

👑 Compiles visual script -> text so that any code built within Princess can be run outside the visual scripting environment

👑 Scripting support for Python and Lua out of the box

👑 Native support for Windows, macOS, and Linux

👑 External plugin support via custom Python scripts

👑 Custom themes out of the box, and blank theme template provided for anyone that wants to make one themselves

👑 Build systems can be built into Princess using Python scripts

👑 Allows user generated configs to provide wider language support

## Building Princess From Source

If you want to build Princess for yourself:

0. This project is built using __C++20__, and you will need __CMake 3.20+__ (scroll down to the resources section for links if you are unfamiliar)

1. Clone the repo

2. Run: __python init.py [--debug or --release or --both] -G [desired_generator]__ in your terminal and your done!
>[!TIP]
>For a complete list of generators run __python init.py [-h or --help]__

> [!NOTE]
>The build output will be generated in __/build/(Debug or Release)__ as an executable

## Motivation

I learned about visual scripting from Scratch (although I've never used Scratch before), and I really enjoy using Blender's shader graph so naturally I looked for an equivalent tool that would allow me to program connecting code nodes together to make something cool. However it quickly became apparent that theres a huge gap in the market for accessible, visually driven coding tools.

As a result I decided to take matters into my own hands and create an easy, good looking and versatile editor for visual scripting. That’s how Princess was born!

I'm hoping that Princess can be as user friendly as VS code, with all the customizability that I crave 😊

Visual scripting is cool, and I don't feel like it's taken very seriously. Princess can be a great entry point for new coders or a refreshing alternative for those tired of plain text editors. Maybe even for people who don't think they can code, you might find that coding is awesome when you see it come to life visually.

My goal with Princess is to make coding more fun, while looking drop dead gorgeous >w<

✨Don't wait become a Python Princess today! ✨ 🏰 👸 🏰

## Resources:

[Latest CMake Download](https://cmake.org/download/)
