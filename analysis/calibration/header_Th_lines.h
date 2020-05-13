//Header  for the lines in Thorium calibration

{

enum eLine{
   Th84, //int 0
   Pb239, //int 1
   Tl277,
   Pb300,
   ee511,
   Tl583,
   Bi727,
   Tl763,
   Bi785,
   Tl861,
   Bi1621,
   Tl2615,
   NLINES,    //int 12 -> This value depends on how many lines I'm working with.
};


	Double_t linesThEn[NLINES] = {0}; //Array of the theoretical energy position of the lines (from literature).
	Double_t linesThEnErr[NLINES] = {0}; //Array of the theoretical on the energy position of the lines (from literature).

linesThEn[Th84] = 84.373;
linesThEnErr[Th84] = 0.003;

linesThEn[Pb239] = 238.632;
linesThEnErr[Pb239] = 0.002;

linesThEn[Tl277] = 277.37;
linesThEnErr[Tl277] = 0.02;

linesThEn[Pb300] = 300.089;
linesThEnErr[Pb300] = 0.012;

linesThEn[ee511] = 510.999;
linesThEnErr[ee511] = 0;

linesThEn[Tl583] = 583.187;
linesThEnErr[Tl583] = 0.002;

linesThEn[Bi727] = 727.33;
linesThEnErr[Bi727] = 0.01;

linesThEn[Tl763] = 763.45;
linesThEnErr[Tl763] = 0.02;

linesThEn[Bi785] = 785.37;
linesThEnErr[Bi785] = 0.09;

linesThEn[Tl861] = 860.53;
linesThEnErr[Tl861] = 0.02;

linesThEn[Bi1621] = 1620.738;
linesThEnErr[Bi785] = 0.010;

linesThEn[Tl2615] = 2614.511;
linesThEnErr[Bi785] = 0.010;


Double_t linesADC[NLINES] = {0}; // Array of ADC channel lines position (from fit).
Double_t linesADCerr[NLINES] = {0}; // Array of the errors on ADC channel lines position (from fit).


//TF1* calFunc[NLINES]; // Handlers array for the functions used to fit the peaks (gaussian + linear pol) and to
                        //  find the center. Don't uncomment in "manual" procedure.

}//end of the header
