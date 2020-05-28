root -b -l <<EOF
gROOT->LoadMacro("isotopes.cpp++")
gROOT->LoadMacro("EffCalcAll.cpp++")
.x EffCalcAll.cpp++(\"/disk/bulk_atp/gator/Simulation_Results/newmaytest\",100000)
.q
EOF
