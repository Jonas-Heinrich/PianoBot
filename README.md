<h1>Piano Bot</h1>
This is a bot that plays "Piano Tap Tiles 2" on an Android Emulator running on a Windows machine.

<h2>Method</h2>
The method it uses is pretty simple:
- make a screenshot of the predefined area (needs to be specified when compiled in PianoBot.h)
- tap the black pixels in the predefined positions (positions get calculated from width, height, x and y position of window)
- if there are any balloon pixels at position x and position y, stop the loop
- else: repeat

It was created in about 2 hours. (C++ back end of getting and analyzing pixels was 99% of the work)

<h2>Results<h2>

<p align="center">
  <img src="https://raw.githubusercontent.com/Phrosten/PianoBot/master/img/Challenges.png"/>
</p>

<h2>Limitating Factors</h2>
- frame rate of Nox Player
- quickness of screenshotting
- click registration  by Windows, Nox, App

<h2>Video Documentation</h2>

<a target="_blank" href="https://youtu.be/DtCzJKR9_n8">Music Example: Byer No.8</a>
<a target="_blank" href="https://youtu.be/TweEm4Yn3zI">Beginner Challenge</a>
<a target="_blank" href="https://youtu.be/W6rAOV55jZQ">Skilled Challenge</a>
