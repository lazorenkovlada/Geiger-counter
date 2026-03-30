void expo_fit() {
    TCanvas *c1 = new TCanvas("c1", "Exponential Fit", 800, 600);
    gStyle->SetOptFit(1111); 
    
    TH1F *h1 = new TH1F("h1", "Time Between Decays;Time interval #Delta t (ms);Number of Events", 150, 0, 15000);
    
    ifstream file("exp_intervals.csv");
    string header;
    file >> header; // Пропускаємо перший рядок (заголовок)
    
    double dt;
    while (file >> dt) {
        h1->Fill(dt);
    }
    file.close();
    
    h1->SetFillColor(kYellow);
    h1->SetLineColor(kBlue);
    
    h1->Fit("expo");
    
    TF1 *fit = h1->GetFunction("expo");
    fit->SetLineColor(kRed);
    fit->SetLineWidth(3);
    
    double exp_lambda = -fit->GetParameter(1);
    double theo_lambda = 20.78 / 60000.0;
    
    c1->SaveAs("expo_result.png");
}
