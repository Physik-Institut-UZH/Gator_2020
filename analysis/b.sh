root -l <<EOF
gROOT->ProcessLine(".L isotopes.cpp++")
gROOT->ProcessLine(".L EffCalcAll.cpp++")
gROOT->ProcessLine(".x EffCalcAll.cpp++(\"/disk/bulk_atp/gator/Simulation_Results/newmaytest\",100000)")
.q
EOF
