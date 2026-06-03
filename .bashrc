echo "########## GATOR .bashrc ##########"

source /app/cern/root_v6.36.10/bin/thisroot.sh ###required for Gator analysis on farm-ui1 as of June 2026
source /app/cern/geant_4.9.3.2/env.sh 
#####################################

export GATORDIR=/disk/gfs_atp/gator ## THIS VARIABLE NEEDS TO BE CHANGED IN NEW INSTALLATIONS!!!!!!
export GATORDIR_summary=/disk/gfs_atp/gator/allsummaryfiles ## THIS VARIABLE REMAINS THE SAME 

export G4WORKDIR=$GATORDIR/simulations/gator_v2.0 ## necessary to substitute env.sh.Sh variables
export G4TMP=$GATORDIR/simulations/gator_v2.0/tmp ## necessary to substitute env.sh.Sh variables
export BATINSTALLDIR=$GATORDIR/BAT-0.9.3 # it may be necessary to install BAT if you are using this code in your local directory

export LD_LIBRARY_PATH=$BATINSTALLDIR/lib64:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/app/physik/freewrl-4.3.0/lib64:$LD_LIBRARY_PATH
export CPATH=$BATINSTALLDIR/include:$CPATH

alias freewrl="/app/physik/freewrl-4.3.0/bin/freewrl"
