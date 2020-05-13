{
	gROOT->ProcessLine("#include <string>");
	gROOT->ProcessLine("#include <fstream>");

	Float_t counts[25000],channel_numbers[25000];
	char tmpchar[1000];
	Char_t FileName1[1000];
	Char_t histo[1000];
	Char_t tmpchar[1000];
	Int_t k=0, Nentries=0, BinCont, i;
	std::string objstr("");

	TCanvas *c1 = new TCanvas("c1","multi spectra",870,500);
	c1->SetLogy();
	TH1F *hs[20];
	char command[2000], line[100], file[200], sampledescr[200];
	char year[4]="",month[2]="",day[2]="",hour[2]="",min[2]="",sec[2]="";
	int date;
	int max_num_ch;
	float sum=0;
	int i=0;
	float dataLT, lifet, meas_t;
	sprintf(command,"ls *.SPE | sed 's/.SPE//'");
	cout<<command<<endl;
	FILE *fpp = gSystem->OpenPipe(command,"r");
	
	while(!feof(fpp))
	{
		fgets(file,sizeof(file),fpp);
	  
		sscanf(file,"%s",&FileName1);
		strcat(FileName1,".SPE");
		cout<<FileName1<<endl;

		ifstream data_in1(FileName1);
		if(!data_in1.good())
		{
			cout << "can't open file" <<  endl; exit(1);
			gROOT->ProcessLine(".q");
		}
	 	if(feof(fpp)) break;
		data_in1.getline(line,sizeof(line)); //first line of the header
		cout<<line<<endl;
		
		data_in1.getline(line,sizeof(line)); // second
		sprintf(sampledescr,"%s",line);
		cout<<sampledescr<<endl;
		
		data_in1.getline(line,sizeof(line)); // third
		cout<<line<<endl;
		data_in1.getline(line,sizeof(line)); // fourth
		cout<<line<<endl;
		data_in1.getline(line,sizeof(line)); // fifth
		cout<<line<<endl;
		data_in1.getline(line,sizeof(line)); // sixth
		cout<<line<<endl;
		data_in1.getline(line,sizeof(line)); // seventh
		cout<<line<<endl;
		data_in1.getline(line,sizeof(line)); // eighth: get start time of acquisition
		objstr = line;
		objstr = objstr.substr(0,objstr.find("\n"));
		std::string datastr("");
		datastr+=objstr.substr(6,4); //The year
		datastr+="-";
		datastr+=objstr.substr(0,2); //The month
		datastr+="-";
		datastr+=objstr.substr(3,2); //The day
		datastr+=" ";
		datastr+=objstr.substr(11); //The time (hh:mm:ss)
		TDatime td;
		td.Set(datastr.c_str());
		date = td.GetYear()*10000+td.GetMonth()*100+td.GetDay();
		cout<<td.GetYear()<<" "<<td.GetMonth()<<" "<<td.GetDay()<<" "<<td.GetHour()<<":"<<td.GetMinute()<<":"<<td.GetSecond()<<" Unix Time: "<<td.Convert()<<endl;
		if(date<20110816)
			max_num_ch = 12300-11;
		else
			max_num_ch = 16380;
		cout<<"max number of channels: "<<max_num_ch<<endl;
	
		sprintf(histo,"hs%d",i);
		hs[i] = new TH1F(histo,"",max_num_ch,0,max_num_ch);
		data_in1.getline(line,sizeof(line));
		cout<<line<<endl;
		data_in1>>meas_t>>lifet;
		cout<<meas_t<<"\t"<<lifet<<endl;
//		td.Set(td.Convert()+meas_t/2.);
		data_in1.getline(line,sizeof(line));
		cout<<line<<endl;
		data_in1.getline(line,sizeof(line));
		cout<<line<<endl;
		dataLT = lifet;
		cout<<"Life time of the measurement: "<<lifet<<endl;


		for(k=0;k<max_num_ch;k++)
		{
			data_in1>>BinCont;
			if(data_in1.eof()) break;
			hs[i]->Fill(k,BinCont);
		}
		hs[i]->Draw();

		sprintf(tmpchar,"%s%d%02d%02d_%02d%02d%02d.txt",FileName1,td.GetYear(),td.GetMonth(),td.GetDay(),td.GetHour(),td.GetMinute(),td.GetSecond());
		cout<<tmpchar<<endl;
		ofstream myfile(tmpchar);

		myfile<<sampledescr<<endl; //The first line is the sample description
		myfile<<dataLT<<endl; //The second line is the life time
		
		for(Int_t j=1; j<max_num_ch; j++)
		{
			myfile<<j<<"\t"<<hs[i]->GetBinContent(j)<<endl;
			if (j>545)
				sum+=hs[i]->GetBinContent(j);
		}
		myfile.close();
		float trigger_rate = sum/dataLT;
		float error=sqrt(sum)/dataLT;
		cout<<"Trigger Rate :"<<"  "<<trigger_rate<<"  Hz"<<"ERROR    "<<error<<endl;
		ofstream trigrate;
		trigrate.open("../Data/trigger_rate/triggerrate.txt",std::ios_base::app);
		trigrate<<td.Convert()<<"  "<<trigger_rate<<"  "<<error<<endl;
		trigrate.close();

		i++;
		sum=0;
		
	}

}
