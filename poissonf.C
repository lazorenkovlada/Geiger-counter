void poissonf() {
    // Відкриваємо зшитий файл
    TTree *tree = new TTree("tree", "Geiger Data");
    // Читаємо 3 колонки
    tree->ReadFile("final_data.csv", "timestamp/C:cpm/I:minute/I", ',');

    TCanvas *c1 = new TCanvas("c1", "Poisson Distribution", 800, 600);
    gStyle->SetOptStat(1111); // Показуватємо блок зі статистикою 

    // Створюємо гістограму (діапазон від 0 до 50 CPM, 50 стовпчиків)
    TH1F *hist = new TH1F("hist", "Radioactive Background Distribution; CPM; Events", 50, 0, 50);

    // Заповнюємо гістограму даними з колонки "cpm"
    tree->Draw("cpm>>hist", "", "goff"); 

    hist->SetFillColor(kYellow);
    hist->SetLineColor(kBlue);
    hist->SetLineWidth(2);
    hist->Draw();
    c1->Update();

    // Знаходимо бокс статистики, який належить гістограмі
    TPaveStats *st = (TPaveStats*)hist->FindObject("stats");
    if (st) {
        // Перемістимо бокс статистики в лівий верхній кут.
        // Координати NDC (Normalized Device Coordinates) від 0 до 1.
        // x-ліво, y-низовий, x-право, y-верхній
        st->SetX1NDC(0.15); // x-ліво. 0.15 - це 15% ширини екрана
        st->SetY1NDC(0.75); // y-низовий. 0.75 - це 75% висоти екрана
        st->SetX2NDC(0.35); // x-право
        st->SetY2NDC(0.85); // y-верхній
    }
    c1->Draw();
    // Створюємо теоретичну функцію Пуассона
    // [0] - це амплітуда (висота), [1] - це лямбда (середнє значення)
    TF1 *poissonFit = new TF1("poissonFit", "[0]*TMath::Poisson(x, [1])", 0, 50);
    
    // Підказуємо програмі початкові параметри, щоб їй було легше рахувати
    poissonFit->SetParameter(0, hist->GetEntries()); 
    poissonFit->SetParameter(1, hist->GetMean());    

    // Накладаємо криву на наші реальні дані (Fit)
    poissonFit->SetLineColor(kRed);
    poissonFit->SetLineWidth(3);
    hist->Fit(poissonFit, "L"); // "L" - метод максимальної правдоподібності 

    TLegend *leg = new TLegend(0.55, 0.75, 0.88, 0.88);
    leg->AddEntry(hist, "Experimental data (462 min)", "f");
    leg->AddEntry(poissonFit, "Poisson fit", "l");
    leg->SetTextSize(0.035);
    leg->Draw();
    c1->SaveAs("poisson_result.png");
}
