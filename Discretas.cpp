#include "pch.h"
#include "Inicio.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main()
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Arrancamos el programa desde el menú de inicio
    Discretas::Inicio formInicio;
    Application::Run(% formInicio);

    return 0;
}