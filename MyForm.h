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

        GroupBox^ grpTabla;
        cli::array<Label^>^ lblX;
        cli::array<Label^>^ lblY;
        cli::array<Label^>^ lblZ;
        cli::array<ComboBox^>^ cmbF;

        GroupBox^ grpMapa;
        cli::array<TextBox^>^ txtMapa; 

        Button^ btnCalcular;
        Button^ btnVolver;
        Label^ lblEcuacion;

    public:
    
        MyForm(int numVars)
        {
            variablesSeleccionadas = numVars;
            numCombinaciones = (variablesSeleccionadas == 2) ? 4 : 8;

            InitializeComponent();
            ConfigurarInterfaz(); 

            this->Text = "Mapa de Karnaugh con " + variablesSeleccionadas + " variables";
        }

    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
   
            int anchoVentana = (variablesSeleccionadas == 2) ? 750 : 850;
            int altoVentana = (variablesSeleccionadas == 2) ? 450 : 550;

            this->Size = System::Drawing::Size(anchoVentana, altoVentana);
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(255, 240, 245); // Fondo Rosado
            this->Font = gcnew System::Drawing::Font("Segoe UI", 10);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
        }

        void ConfigurarInterfaz()
        {
         
            grpTabla = gcnew GroupBox();
            grpTabla->Text = "Tabla de verdad";
            grpTabla->Location = Point(20, 20);
            grpTabla->Size = System::Drawing::Size((variablesSeleccionadas == 2 ? 280 : 320), (variablesSeleccionadas == 2 ? 280 : 420));
            grpTabla->ForeColor = Color::FromArgb(150, 60, 100);
            grpTabla->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(grpTabla);

            Label^ lblHeadX = gcnew Label(); lblHeadX->Text = "x"; lblHeadX->Location = Point(50, 40); lblHeadX->AutoSize = true;
            Label^ lblHeadY = gcnew Label(); lblHeadY->Text = "y"; lblHeadY->Location = Point(110, 40); lblHeadY->AutoSize = true;
            grpTabla->Controls->Add(lblHeadX); grpTabla->Controls->Add(lblHeadY);

            int posF = 170;
            if (variablesSeleccionadas == 3) {
                Label^ lblHeadZ = gcnew Label(); lblHeadZ->Text = "z"; lblHeadZ->Location = Point(170, 40); lblHeadZ->AutoSize = true;
                grpTabla->Controls->Add(lblHeadZ);
                posF = 230; 
            }

            // Cabecera F
            Label^ lblHeadF = gcnew Label(); lblHeadF->Text = "f"; lblHeadF->Location = Point(posF + 15, 40); lblHeadF->AutoSize = true;
            grpTabla->Controls->Add(lblHeadF);

            lblX = gcnew cli::array<Label^>(numCombinaciones);
            lblY = gcnew cli::array<Label^>(numCombinaciones);
            if (variablesSeleccionadas == 3) lblZ = gcnew cli::array<Label^>(numCombinaciones);
            cmbF = gcnew cli::array<ComboBox^>(numCombinaciones);

            cli::array<String^>^ valX2 = { "0", "0", "1", "1" };
            cli::array<String^>^ valY2 = { "0", "1", "0", "1" };

            cli::array<String^>^ valX3 = { "0", "0", "0", "0", "1", "1", "1", "1" };
            cli::array<String^>^ valY3 = { "0", "0", "1", "1", "0", "0", "1", "1" };
            cli::array<String^>^ valZ3 = { "0", "1", "0", "1", "0", "1", "0", "1" };

            for (int i = 0; i < numCombinaciones; i++) {
                int yPos = 80 + (i * 35);

                lblX[i] = gcnew Label(); lblX[i]->Text = (variablesSeleccionadas == 2) ? valX2[i] : valX3[i];
                lblX[i]->Location = Point(50, yPos); lblX[i]->AutoSize = true;
                grpTabla->Controls->Add(lblX[i]);

                lblY[i] = gcnew Label(); lblY[i]->Text = (variablesSeleccionadas == 2) ? valY2[i] : valY3[i];
                lblY[i]->Location = Point(110, yPos); lblY[i]->AutoSize = true;
                grpTabla->Controls->Add(lblY[i]);

                if (variablesSeleccionadas == 3) {
                    lblZ[i] = gcnew Label(); lblZ[i]->Text = valZ3[i];
                    lblZ[i]->Location = Point(170, yPos); lblZ[i]->AutoSize = true;
                    grpTabla->Controls->Add(lblZ[i]);
                }

                cmbF[i] = gcnew ComboBox();
                cmbF[i]->Items->Add("0"); cmbF[i]->Items->Add("1");
                cmbF[i]->DropDownStyle = ComboBoxStyle::DropDownList;
                cmbF[i]->SelectedIndex = 0;
                cmbF[i]->Location = Point(posF, yPos - 3); cmbF[i]->Size = System::Drawing::Size(50, 20);
                grpTabla->Controls->Add(cmbF[i]);
            }


            grpMapa = gcnew GroupBox();
            grpMapa->Text = "Mapa de Karnaugh";
            grpMapa->Location = Point((variablesSeleccionadas == 2 ? 340 : 380), 20);
            grpMapa->Size = System::Drawing::Size((variablesSeleccionadas == 2 ? 350 : 420), 280);
            grpMapa->ForeColor = Color::FromArgb(150, 60, 100);
            grpMapa->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);
            this->Controls->Add(grpMapa);

            Label^ lblHeadXNeg = gcnew Label(); lblHeadXNeg->Text = "x'"; lblHeadXNeg->Location = Point(40, 90); lblHeadXNeg->AutoSize = true;
            Label^ lblHeadXPos = gcnew Label(); lblHeadXPos->Text = "x";  lblHeadXPos->Location = Point(40, 140); lblHeadXPos->AutoSize = true;
            grpMapa->Controls->Add(lblHeadXNeg); grpMapa->Controls->Add(lblHeadXPos);

            int numColumnasMapa = (variablesSeleccionadas == 2) ? 2 : 4;
            txtMapa = gcnew cli::array<TextBox^>(numCombinaciones);

            cli::array<String^>^ head2 = { "y'", "y" };
            cli::array<String^>^ head3 = { "y'z'", "y'z", "yz", "yz'" }; // Código Gray

            for (int col = 0; col < numColumnasMapa; col++) {
                Label^ lblCol = gcnew Label();
                lblCol->Text = (variablesSeleccionadas == 2) ? head2[col] : head3[col];
                lblCol->Location = Point(90 + (col * 60), 50);
                lblCol->AutoSize = true;
                grpMapa->Controls->Add(lblCol);

                txtMapa[col] = CrearCeldaMapa(85 + (col * 60), 85);
                grpMapa->Controls->Add(txtMapa[col]);

                txtMapa[col + numColumnasMapa] = CrearCeldaMapa(85 + (col * 60), 135);
                grpMapa->Controls->Add(txtMapa[col + numColumnasMapa]);
            }


            btnCalcular = gcnew Button();
            btnCalcular->Text = "Calcular";
            btnCalcular->Location = Point((variablesSeleccionadas == 2 ? 230 : 300), 200);
            btnCalcular->Size = System::Drawing::Size(90, 40);
            btnCalcular->BackColor = Color::FromArgb(219, 112, 147);
            btnCalcular->ForeColor = Color::White;
            btnCalcular->FlatStyle = FlatStyle::Flat;
            btnCalcular->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            btnCalcular->Cursor = Cursors::Hand;
            btnCalcular->Click += gcnew EventHandler(this, &MyForm::btnCalcular_Click);
            grpMapa->Controls->Add(btnCalcular);

            lblEcuacion = gcnew Label();
            lblEcuacion->Text = "F = ";
            lblEcuacion->Location = Point((variablesSeleccionadas == 2 ? 340 : 380), 330);
            lblEcuacion->AutoSize = true;
            lblEcuacion->ForeColor = Color::FromArgb(150, 60, 100);
            lblEcuacion->Font = gcnew System::Drawing::Font("Segoe UI", 12, FontStyle::Bold);
            this->Controls->Add(lblEcuacion);

            btnVolver = gcnew Button();
            btnVolver->Text = "Volver";
            btnVolver->Location = Point((variablesSeleccionadas == 2 ? 600 : 700), (variablesSeleccionadas == 2 ? 350 : 450));
            btnVolver->Size = System::Drawing::Size(90, 35);
            btnVolver->BackColor = Color::FromArgb(240, 180, 200);
            btnVolver->ForeColor = Color::FromArgb(100, 40, 60);
            btnVolver->FlatStyle = FlatStyle::Flat;
            btnVolver->Font = gcnew System::Drawing::Font("Segoe UI", 9, FontStyle::Bold);
            btnVolver->Cursor = Cursors::Hand;
            btnVolver->Click += gcnew EventHandler(this, &MyForm::btnVolver_Click);
            this->Controls->Add(btnVolver);
        }

        TextBox^ CrearCeldaMapa(int posX, int posY)
        {
            TextBox^ txt = gcnew TextBox();
            txt->Location = Point(posX, posY);
            txt->Size = System::Drawing::Size(40, 25);
            txt->ReadOnly = true;
            txt->TextAlign = HorizontalAlignment::Center;
            txt->BackColor = Color::White;
            txt->ForeColor = Color::FromArgb(150, 60, 100);
            txt->Font = gcnew System::Drawing::Font("Segoe UI", 10, FontStyle::Bold);

            return txt;
        }

        void btnCalcular_Click(Object^ sender, EventArgs^ e)
        {
            KarnaughMap* mapa = new KarnaughMap(variablesSeleccionadas);

            if (variablesSeleccionadas == 2) {
                int f00 = System::Convert::ToInt32(cmbF[0]->SelectedItem);
                int f01 = System::Convert::ToInt32(cmbF[1]->SelectedItem);
                int f10 = System::Convert::ToInt32(cmbF[2]->SelectedItem);
                int f11 = System::Convert::ToInt32(cmbF[3]->SelectedItem);

                mapa->configurarCelda(0, 0, f00); mapa->configurarCelda(0, 1, f01);
                mapa->configurarCelda(1, 0, f10); mapa->configurarCelda(1, 1, f11);

                txtMapa[0]->Text = mapa->obtenerValorCelda(0, 0).ToString();
                txtMapa[1]->Text = mapa->obtenerValorCelda(0, 1).ToString();
                txtMapa[2]->Text = mapa->obtenerValorCelda(1, 0).ToString();
                txtMapa[3]->Text = mapa->obtenerValorCelda(1, 1).ToString();
            }
            else if (variablesSeleccionadas == 3) {
                int v0 = System::Convert::ToInt32(cmbF[0]->SelectedItem); // x'y'z'
                int v1 = System::Convert::ToInt32(cmbF[1]->SelectedItem); // x'y'z
                int v2 = System::Convert::ToInt32(cmbF[2]->SelectedItem); // x'yz'
                int v3 = System::Convert::ToInt32(cmbF[3]->SelectedItem); // x'yz
                int v4 = System::Convert::ToInt32(cmbF[4]->SelectedItem); // xy'z'
                int v5 = System::Convert::ToInt32(cmbF[5]->SelectedItem); // xy'z
                int v6 = System::Convert::ToInt32(cmbF[6]->SelectedItem); // xyz'
                int v7 = System::Convert::ToInt32(cmbF[7]->SelectedItem); // xyz

                mapa->configurarCelda(0, 0, v0); mapa->configurarCelda(0, 1, v1);
                mapa->configurarCelda(0, 3, v2); mapa->configurarCelda(0, 2, v3);

                mapa->configurarCelda(1, 0, v4); mapa->configurarCelda(1, 1, v5);
                mapa->configurarCelda(1, 3, v6); mapa->configurarCelda(1, 2, v7);
                txtMapa[0]->Text = v0.ToString(); txtMapa[1]->Text = v1.ToString();
                txtMapa[2]->Text = v3.ToString(); txtMapa[3]->Text = v2.ToString();
                txtMapa[4]->Text = v4.ToString(); txtMapa[5]->Text = v5.ToString();
                txtMapa[6]->Text = v7.ToString(); txtMapa[7]->Text = v6.ToString();
            }

            std::string resultadoStr = mapa->resolverMapa();
            lblEcuacion->Text = "F = " + gcnew String(resultadoStr.c_str());

            delete mapa;
        }

        void btnVolver_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}