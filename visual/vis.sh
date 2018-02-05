#!/bin/sh
pat=$PWD/visual/visual.php
open "http://localhost:8080`echo $pat | sed 's/^.*htdocs//'`"