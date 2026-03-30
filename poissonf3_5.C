void poissonf3_5() {
    // Відкриваємо зшитий файл
    TTree *tree = new TTree("tree", "Geiger Data");
    // Читаємо 3 колонки
    tree->ReadFile("final_data3_5.csv", "timestamp/C:cpm/I:minute/I", ',');

    TCanvas *c1 = new TCanvas("c1", "Poisson Distribution (4320)", 800, 600);
    gStyle->SetOptStat(1111); // Показуватємо блок зі статистикою 

    // Створюємо гістограму (діапазон від 0 до 50 CPM, 50 стовпчиків)
    TH1F *hist = new TH1F("hist", "Radioactive Background Distribution; CPM; Events", 50, 0, 50);

    // Заповнюємо гістограму даними з колонки "cpm"
    tree->Draw("cpm>>hist", "", "goff"); 

    hist->SetFillColor(kYellow);
    hist->SetLineColor(kBlue);
    hist->SetLineWidth(2);
    hist->Draw();   

    c1->SaveAs("poisson_result3_5.png");
}
