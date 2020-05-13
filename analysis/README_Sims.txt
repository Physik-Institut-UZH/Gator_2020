{\rtf1\ansi\ansicpg1252\cocoartf1265\cocoasubrtf210
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural

\f0\fs24 \cf0 This is a how-to on simulations for Gator screening analysis.\
(needs more details)\
\
\
1. Create sample geometry\
	%gator_1.2 creates a visualisation of the geometry\
\
2. \
	compile GlobGeomInfo (% make -f GlobGeomInfo)\
	Run %GlobGeomInfo -v [name of PhysicalVolume as called in the sample geometry]\
	This generates location information for the physical volume of the sample. \
\
3. enter geometry info into macros (manually)\
\
4. enter info into MasterSubmit2.py file for running sims\
\
5. from sims, generated files:\
\
6. MergeFiles.py\
\
7. EffCalcAll.cpp to get line efficiencies \'85 generates lines.list\
	may need spearate analysis for special lines (e.g. Ag-110 in PMTs, change in Cs contamination requires separate analysis for this line).\
\
8. Proceed to analysis with lines.list files\
\
\
\
\
\
Last update October 1, 2014}