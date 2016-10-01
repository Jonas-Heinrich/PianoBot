<h1>Piano Bot</h1>
This is a bot that plays "Piano Tap Tiles 2" on an Android Emulator running on a Windows machine.

<h2>Method</h2>
The method it uses is pretty simple:
- make a screenshot of the predefined area (needs to be specified when compiled in PianoBot.h)
- tap the black pixels in the predefined positions (positions get calculated from width, height, x and y position of window)
- if there are any baloon pixels at position x and position y, stop the loop
- else: repeat

It was created in about 2 hours. (C++ backend of getting and analyzing pixels was 99% of the work)

<h2>Results<h2>

<p align="center">
  <img src="https://github.com/Phrosten/PianoBot/tree/master/results/challengs.png"/>
</p>
