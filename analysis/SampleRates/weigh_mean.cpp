void weigh_mean(){

	string cmd("");
	
	vector<double> val;
	vector<double> err;
	
	double value, error;
	
	
	while(cmd!=string("q")&&cmd!=string("f")&&cmd!=string("Q")&&cmd!=string("F")){
		
		
		if(cmd==string("N")||cmd==string("n")){
			cout << "\nInsert value: ";
			if(cin >> value){
				cout << endl;
				val.push_back(value);
			}else{
				cout << "\nError the value inserted is not a number!!! Exiting" << endl;
				return;
			}
			
			
			cout << "\Insert value error: ";
			if(cin >> value){
				cout << endl;
				err.push_back(error);
			}else{
				cout << "\nError the value inserted is not a number!!! Exiting" << endl;
				return;
			}
			
		}
		
		cout << "\nInsert a command:\n" << endl;
		
		cout << "Q --> Quit" << endl;
		cout << "F --> Finish acquisition (work out the weighted mean)" << endl;
		cout << "N --> New value and error entry" << endl << endl;
		
		cin >> cmd;
		cout << endl;
	}
	
	if(cmd==string("Q")||cmd==string("q")) return;
	
	int entries = err.size();
	
	double result=0, result_err=0, num=0, den=0;
	
	for(int i=0; i<entries; i++){
		num += val[i]*pow(err[i],-2);
		den += pow(err[i],-2);
	}
	
	cout << "\nThe weighted mean is: " << num/den << end;
	
	den = 0;
	for(int i=0; i<entries; i++){
		den += pow(err[i],-2);
	}
	
	cout << "The weighted error is: " << 1./sqrt(den) << endl;
	
	return;

}