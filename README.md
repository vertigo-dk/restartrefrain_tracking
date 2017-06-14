Tracking for restart / refrain project 2017

Takes OSC incoming messages from the DAC-Bymodel_Tracking app
Processes the messages and sends OSC to Mikkels Max patch.

Format of OSC messages:

/trackgroup/index i(active track)
/enabled (bool)

There are 8 trackgroups. Within each group a number from 0-2 indicates if Søs, Jens or Mikkels track should be turned on.
'enabled' indicates if the installation is active (if there are any users)

NOTES:

Sometimes you need to replug the power cable of the Kinect to get DAC-Bymodel_Tracking working

You can also record data and play them back using this small command line app:

https://github.com/markcerqueira/oscreplayer

outcomment the line starting with ruby (check that your version of ruby is bigger than 1.9.3 with ruby -v)

Record:

./oscrecorder --port 8111 --filename osc_data.yml

Playback on another port:

./oscplayer -a 192.168.1.28 -p 8112 -f osc_data.yml