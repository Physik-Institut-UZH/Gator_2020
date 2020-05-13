void sigmacalc(const TF1* calib_fcn_fw, const Double_t ADCcenter, const Double_t ADCsigma, const Double_t ADCsigma_err, Double_t& ENRsigma, Double_t& ENRsigma_err){
	//This gives the sigma value for the resolution in energy domain without doing again the calibration fits in energy domain
	
	
	Double_t upvalue, lowvalue;
	
	upvalue = calib_fcn_fw -> Eval(ADCcenter + ADCsigma);
	lowvalue = calib_fcn_fw -> Eval(ADCcenter - ADCsigma);
	
	ENRsigma = (upvalue - lowvalue)/2;
	
	ENRsigma_err = ENRsigma*(ADCsigma_err/ADCsigma); //Here I do a very heavy assumption: the relative error remains the same
	
	return;
	
}