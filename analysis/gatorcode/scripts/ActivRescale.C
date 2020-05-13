void ActivRescale(){
	
	Double_t activity = 1.39; //Arbitrary units
	Double_t half_life = 6.480; //In days
	Double_t runtime = 993600;//In secs
	
	half_life *= (24.*3600.);
	
	double timeratio = runtime*log(2)/(half_life);
	
	cout << endl << "Rescaled activity = " << activity*timeratio/(1-TMath::Exp(-timeratio)) << endl << endl;
	
	return;
	
}