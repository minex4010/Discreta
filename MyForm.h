#pragma once
#include "KarnaughMap.h"
#include <string>

namespace Discretas {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        int variablesSeleccionadas;
        int numCombinaciones;

        Panel^ pnlTabla;
        cli::array<Label^>^ lblX;
        cli::array<Label^>^ lblY;
        cli::array<Label^>^ lblZ;
        cli::array<Label^>^ lblW;
        cli::array<ComboBox^>^ cmbF;

        Panel^ pnlMapa;
        cli::array<TextBox^>^ txtMapa;

        Button^ btnCalcular;
        Button^ btnVolver;
        Label^ lblTituloFuncion;
        Label^ lblEcuacion;

    public:
        MyForm(int numVars)
        {
            variablesSeleccionadas = numVars;
            numCombinaciones = (variablesSeleccionadas == 2) ? 4 : (variablesSeleccionadas == 3 ? 8 : 16);

            InitializeComponent();
            ConfigurarInterfaz();

            this->Text = "Mapa de Karnaugh con " + variablesSeleccionadas + " variables";
        }

    protected:
        ~MyForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->Size = System::Drawing::Size(950, 600);
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = Color::DarkGray;
            this->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
        }

        void ConfigurarInterfaz()
        {
 
            pnlTabla = gcnew Panel();
            pnlTabla->BackColor = Color::LightSkyBlue;
            pnlTabla->Location = Point(20, 20);
            pnlTabla->Size = System::Drawing::Size((variablesSeleccionadas == 4 ? 260 : 200), 520);
            this->Controls->Add(pnlTabla);

            Label^ lblTituloTabla = gcnew Label();
            lblTituloTabla->Text = "Tabla de verdad";
            lblTituloTabla->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
            lblTituloTabla->Location = Point(20, 10);
            lblTituloTabla->AutoSize = true;
            pnlTabla->Controls->Add(lblTituloTabla);

            int cX = 30, cY = 70, cZ = 110, cW = 150, cF = 190;
            if (variablesSeleccionadas == 2) { cF = 110; }
            else if (variablesSeleccionadas == 3) { cF = 150; }

            Label^ headX = gcnew Label(); headX->Text = "x"; headX->Location = Point(cX, 45); headX->AutoSize = true; pnlTabla->Controls->Add(headX);
            Label^ headY = gcnew Label(); headY->Text = "y"; headY->Location = Point(cY, 45); headY->AutoSize = true; pnlTabla->Controls->Add(headY);
            if (variablesSeleccionadas >= 3) { Label^ headZ = gcnew Label(); headZ->Text = "z"; headZ->Location = Point(cZ, 45); headZ->AutoSize = true; pnlTabla->Controls->Add(headZ); }
            if (variablesSeleccionadas == 4) { Label^ headW = gcnew Label(); headW->Text = "w"; headW->Location = Point(cW, 45); headW->AutoSize = true; pnlTabla->Controls->Add(headW); }
            Label^ headF = gcnew Label(); headF->Text = "f"; headF->Location = Point(cF + 10, 45); headF->AutoSize = true; pnlTabla->Controls->Add(headF);

            lblX = gcnew cli::array<Label^>(numCombinaciones);
            lblY = gcnew cli::array<Label^>(numCombinaciones);
            if (variablesSeleccionadas >= 3) lblZ = gcnew cli::array<Label^>(numCombinaciones);
            if (variablesSeleccionadas == 4) lblW = gcnew cli::array<Label^>(numCombinaciones);
            cmbF = gcnew cli::array<ComboBox^>(numCombinaciones);

            int startY = 75;
            int stepY = (variablesSeleccionadas == 4) ? 26 : 35;

            for (int i = 0; i < numCombinaciones; i++) {
                int rowY = startY + (i * stepY);
                int bitX = (i >> (variablesSeleccionadas - 1)) & 1;
                int bitY = (i >> (variablesSeleccionadas - 2)) & 1;

                lblX[i] = gcnew Label(); lblX[i]->Text = bitX.ToString(); lblX[i]->Location = Point(cX, rowY); lblX[i]->AutoSize = true; pnlTabla->Controls->Add(lblX[i]);
                lblY[i] = gcnew Label(); lblY[i]->Text = bitY.ToString(); lblY[i]->Location = Point(cY, rowY); lblY[i]->AutoSize = true; pnlTabla->Controls->Add(lblY[i]);

                if (variablesSeleccionadas >= 3) {
                    int bitZ = (i >> (variablesSeleccionadas - 3)) & 1;
                    lblZ[i] = gcnew Label(); lblZ[i]->Text = bitZ.ToString(); lblZ[i]->Location = Point(cZ, rowY); lblZ[i]->AutoSize = true; pnlTabla->Controls->Add(lblZ[i]);
                }
                if (variablesSeleccionadas == 4) {
                    int bitW = i & 1;
                    lblW[i] = gcnew Label(); lblW[i]->Text = bitW.ToString(); lblW[i]->Location = Point(cW, rowY); lblW[i]->AutoSize = true; pnlTabla->Controls->Add(lblW[i]);
                }

                cmbF[i] = gcnew ComboBox();
                cmbF[i]->Items->Add("0"); cmbF[i]->Items->Add("1");
                cmbF[i]->DropDownStyle = ComboBoxStyle::DropDownList;
                cmbF[i]->SelectedIndex = 0;
                cmbF[i]->Size = System::Drawing::Size(45, 20);
                cmbF[i]->Location = Point(cF, rowY - 3);
                pnlTabla->Controls->Add(cmbF[i]);
            }

            pnlMapa = gcnew Panel();
            pnlMapa->BackColor = Color::LightPink;
            pnlMapa->Location = Point(320, 20);
            pnlMapa->Size = System::Drawing::Size(580, 320);
            this->Controls->Add(pnlMapa);

            int numFilasMapa = (variablesSeleccionadas == 4) ? 4 : 2;
            int numColumnasMapa = (variablesSeleccionadas == 2) ? 2 : 4;
            txtMapa = gcnew cli::array<TextBox^>(numCombinaciones);

            int startXMapa = 100, startYMapa = 80;

            // DIBUJAR CAJAS DEL MAPA
            for (int r = 0; r < numFilasMapa; r++) {
                for (int c = 0; c < numColumnasMapa; c++) {
                    int index = r * numColumnasMapa + c;
                    txtMapa[index] = gcnew TextBox();
                    txtMapa[index]->Location = Point(startXMapa + (c * 60), startYMapa + (r * 40));
                    txtMapa[index]->Size = System::Drawing::Size(45, 25);
                    txtMapa[index]->ReadOnly = true;
                    txtMapa[index]->TextAlign = HorizontalAlignment::Center;
                    pnlMapa->Controls->Add(txtMapa[index]);
                }
            }

 


            cli::array<String^>^ leftLabels = (variablesSeleccionadas == 4) ? gcnew cli::array<String^>{ "x'", "x'", "x", "x" } : gcnew cli::array<String^>{ "x'", "x" };
            for (int r = 0; r < numFilasMapa; r++) {
                Label^ lbl = gcnew Label(); lbl->Text = leftLabels[r];
                lbl->Location = Point(startXMapa - 35, startYMapa + (r * 40) + 5);
                lbl->AutoSize = true; pnlMapa->Controls->Add(lbl);
            }

            cli::array<String^>^ topLabels;
            if (variablesSeleccionadas >= 3) {
                topLabels = gcnew cli::array<String^>{ "y'", "y'", "y", "y" };
            }
            else {
                topLabels = gcnew cli::array<String^>{ "y'", "y" };
            }
            for (int c = 0; c < numColumnasMapa; c++) {
                Label^ lbl = gcnew Label(); lbl->Text = topLabels[c];
                lbl->Location = Point(startXMapa + (c * 60) + 15, startYMapa - 25);
                lbl->AutoSize = true; pnlMapa->Controls->Add(lbl);
            }

            if (variablesSeleccionadas >= 3) {
                cli::array<String^>^ botLabels = gcnew cli::array<String^>{ "z'", "z", "z", "z'" };
                for (int c = 0; c < numColumnasMapa; c++) {
                    Label^ lbl = gcnew Label(); lbl->Text = botLabels[c];
                    lbl->Location = Point(startXMapa + (c * 60) + 15, startYMapa + (numFilasMapa * 40) + 10);
                    lbl->AutoSize = true; pnlMapa->Controls->Add(lbl);
                }
            }

            if (variablesSeleccionadas == 4) {
                cli::array<String^>^ rightLabels = gcnew cli::array<String^>{ "w'", "w", "w", "w'" };
                for (int r = 0; r < numFilasMapa; r++) {
                    Label^ lbl = gcnew Label(); lbl->Text = rightLabels[r];
                    lbl->Location = Point(startXMapa + (numColumnasMapa * 60) + 10, startYMapa + (r * 40) + 5);
                    lbl->AutoSize = true; pnlMapa->Controls->Add(lbl);
                }
            }

            btnCalcular = gcnew Button();
            btnCalcular->Text = "Calcular";
            btnCalcular->Location = Point(420, 120);
            btnCalcular->Size = System::Drawing::Size(110, 45);
            btnCalcular->BackColor = Color::Violet;
            btnCalcular->FlatStyle = FlatStyle::Flat;
            btnCalcular->FlatAppearance->BorderColor = Color::Blue;
            btnCalcular->FlatAppearance->BorderSize = 2;
            btnCalcular->Font = gcnew System::Drawing::Font("Segoe UI", 11, FontStyle::Bold);
            btnCalcular->Cursor = Cursors::Hand;
            btnCalcular->Click += gcnew EventHandler(this, &MyForm::btnCalcular_Click);
            pnlMapa->Controls->Add(btnCalcular);

            lblTituloFuncion = gcnew Label();
            lblTituloFuncion->Text = "Funcion booleana:";
            lblTituloFuncion->Location = Point(320, 380);
            lblTituloFuncion->AutoSize = true;
            lblTituloFuncion->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
            this->Controls->Add(lblTituloFuncion);

            lblEcuacion = gcnew Label();
            lblEcuacion->Text = "";
            lblEcuacion->Location = Point(320, 430);
            lblEcuacion->AutoSize = true;
            lblEcuacion->Font = gcnew System::Drawing::Font("Segoe UI", 14);
            lblEcuacion->ForeColor = Color::Black;
            this->Controls->Add(lblEcuacion);

            btnVolver = gcnew Button();
            btnVolver->Text = "Volver al Menú";
            btnVolver->Location = Point(760, 480);
            btnVolver->Size = System::Drawing::Size(140, 40);
            btnVolver->Click += gcnew EventHandler(this, &MyForm::btnVolver_Click);
            this->Controls->Add(btnVolver);
        }

        void btnCalcular_Click(Object^ sender, EventArgs^ e)
        {
            KarnaughMap* mapa = new KarnaughMap(variablesSeleccionadas);

            cli::array<int>^ v = gcnew cli::array<int>(16);
            for (int i = 0; i < numCombinaciones; i++) {
                v[i] = (cmbF[i]->Text == "1") ? 1 : 0;
            }

            if (variablesSeleccionadas == 2) {
                mapa->configurarCelda(0, 0, v[0]); mapa->configurarCelda(0, 1, v[1]);
                mapa->configurarCelda(1, 0, v[2]); mapa->configurarCelda(1, 1, v[3]);
            }
            else if (variablesSeleccionadas == 3) {
                mapa->configurarCelda(0, 0, v[0]); mapa->configurarCelda(0, 1, v[1]);
                mapa->configurarCelda(0, 3, v[2]); mapa->configurarCelda(0, 2, v[3]);

                mapa->configurarCelda(1, 0, v[4]); mapa->configurarCelda(1, 1, v[5]);
                mapa->configurarCelda(1, 3, v[6]); mapa->configurarCelda(1, 2, v[7]);
            }
            else if (variablesSeleccionadas == 4) {
                mapa->configurarCelda(0, 0, v[0]); mapa->configurarCelda(0, 1, v[1]);
                mapa->configurarCelda(0, 3, v[2]); mapa->configurarCelda(0, 2, v[3]);

                mapa->configurarCelda(1, 0, v[4]); mapa->configurarCelda(1, 1, v[5]);
                mapa->configurarCelda(1, 3, v[6]); mapa->configurarCelda(1, 2, v[7]);

                mapa->configurarCelda(2, 0, v[12]); mapa->configurarCelda(2, 1, v[13]);
                mapa->configurarCelda(2, 3, v[14]); mapa->configurarCelda(2, 2, v[15]);

                mapa->configurarCelda(3, 0, v[8]); mapa->configurarCelda(3, 1, v[9]);
                mapa->configurarCelda(3, 3, v[10]); mapa->configurarCelda(3, 2, v[11]);
            }

            int numFilasMapa = (variablesSeleccionadas == 4) ? 4 : 2;
            int numColumnasMapa = (variablesSeleccionadas == 2) ? 2 : 4;

            for (int r = 0; r < numFilasMapa; r++) {
                for (int c = 0; c < numColumnasMapa; c++) {
                    int index = r * numColumnasMapa + c;
                    txtMapa[index]->Text = mapa->obtenerValorCelda(r, c).ToString();
                }
            }

            std::string resultadoStr = mapa->resolverMapa();
            lblEcuacion->Text = gcnew String(resultadoStr.c_str());

            delete mapa;
        }

        void btnVolver_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}