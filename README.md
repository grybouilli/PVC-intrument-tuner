# The project

## Context 

This repo contains the code made to run a maker's project. The project was led for a class during my second year in a French engineering school. The main purpose of the course was to get to know the maker's culture, to dig into arduino development and to learn how to use tools such as 3D printers and laser cutter.

You can learn more about the project here : [Project Page](https://www.eirlab.net/2023/03/02/marble-machine/)

## Goal

The overall project goal is to create a small marble machine; marbles would fall a pvc xylophone like instrument and then be loaded back into the machine. 

This part of the project manages the tone of the pvc tubes of the instrument. It was decided to use eight tubes so a full octave is reachable. The tubes can then be tuned a certain way depending on their depth so that we can switch from one musical range to another. Hence, each tube should be tunable to either its natural chord, the flat chord or the sharp chord of its corresponding note.

The depth of each tube is controlled by a rack that slides a panel up and down inside the tube itself. The rack slides with the help of a stepper motor.

# The repo

## The code 

The code you will find here allows you to take full control of the pvc instrument by tuning each tube to a desired note.

## If you want to run things at home...

* You will need a bunch of stepper motors (the ones used in this project were the 28BYJ-48);
* You can find the models for the laser cutter here : [Cardboard Model](https://cad.onshape.com/documents/4a0008826c22b29dc936e1e9/w/e494817c4de656d3e8d2234e/e/544844275ed85f03e61b4b3b?renderMode=0&uiState=64404325070f4a0de0c46094);
* You should check the [Project Page](https://www.eirlab.net/2023/03/02/marble-machine/) for guidance on the assembling of things.


