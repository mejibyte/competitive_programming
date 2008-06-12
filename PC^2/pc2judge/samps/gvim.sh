#!/bin/sh

# File:    gvim.sh
# Purpose: Used as a wrapper around gvim to generate the proper
#          xml output expected of a validator.
#          NOTE: gvim cannot be used as an auto-judger
# Author:  pc2@ecs.csus.edu
# Revised: $Date: 2006/05/07 21:27:31 $
# 
# $Id: gvim.sh,v 1.1 2006/05/07 21:27:31 boudreat Exp $

cat <<EOM > $4
<?xml version="1.0"?>
<result security="$4" outcome="something"/>
EOM
gvim -d $2 $3
