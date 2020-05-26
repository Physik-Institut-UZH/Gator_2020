echo "########## GATOR .bashrc ##########"

source /app/cern/root_v5.34.38/bin/thisroot.sh ###required for Gator analysis on farm-ui as of Feb 2019 
source /app/cern/geant_4.9.3.2/env.sh 
#####################################

export G4WORKDIR=/disk/bulk_atp/gator/simulations/gator_v2.0 ## necessary to substitute env.sh.Sh variables
export G4TMP=/disk/bulk_atp/gator/simulations/gator_v2.0/tmp ## necessary to substitute env.sh.Sh variables
export BATINSTALLDIR=/disk/bulk_atp/gator/BAT-0.9.3

export LD_LIBRARY_PATH=$BATINSTALLDIR/lib64:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/app/physik/freewrl-4.3.0/lib64:$LD_LIBRARY_PATH
export CPATH=$BATINSTALLDIR/include:$CPATH

alias freewrl="/app/physik/freewrl-4.3.0/bin/freewrl"
