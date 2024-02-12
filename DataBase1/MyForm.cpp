#include "MyForm.h"
#include <Windows.h>
#include <iostream>
#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include <string>

using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System;
using namespace DataBase1;
using namespace std;
using namespace System::Xml;
static bool folderSelected = false;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MyForm^ myForm = gcnew MyForm();
    Application::Run(myForm);
    return 0;
}
public ref class MyPictureBoxForm : public Form
{
public:
    MyPictureBoxForm(String^ imagePath)
    {
        PictureBox^ pictureBox = gcnew PictureBox();
        pictureBox->ImageLocation = imagePath;
        pictureBox->SizeMode = PictureBoxSizeMode::Zoom;  // Растягиваем изображение на всю форму
        pictureBox->Dock = DockStyle::Fill;  // Заполняем всю доступную область формы

        this->Controls->Add(pictureBox);
    }
};
public ref class InfoAndPictureForm : public Form
{
private:
    Label^ infoLabel;
    PictureBox^ pictureBox;
    Label^ accessLevelLabel; // Добавляем новый Label для отображения уровня доступа

public:
    InfoAndPictureForm(String^ info, String^ imagePath, int accessLevel)
    {
        // Инициализация компонентов формы
        InitializeComponent();

        // Установка текста для Label
        infoLabel->Text = info;

        // Установка текста для Label с уровнем доступа
        accessLevelLabel->Text = "Уровень доступа: " + accessLevel.ToString();

        // Загрузка и отображение изображения в PictureBox
        if (File::Exists(imagePath))
        {
            pictureBox->Image = Image::FromFile(imagePath);
            pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
        }
    }

private:
    void InitializeComponent()
    {
        // Создание компонентов формы
        infoLabel = gcnew Label();
        pictureBox = gcnew PictureBox();
        accessLevelLabel = gcnew Label(); // Инициализация нового Label

        // Настройка формы
        this->Text = "Информация и изображение";
        this->Size = System::Drawing::Size(600, 450); // Увеличиваем высоту для нового Label

        // Настройка Label
        infoLabel->AutoSize = true;
        infoLabel->Location = Point(10, 10);

        // Настройка Label с уровнем доступа
        accessLevelLabel->AutoSize = true;
        accessLevelLabel->Location = Point(10, 320); // Располагаем под изображением

        // Настройка PictureBox
        pictureBox->Location = Point(10, 40);
        pictureBox->Size = System::Drawing::Size(500, 270); // Уменьшаем высоту изображения

        // Добавление компонентов на форму
        this->Controls->Add(infoLabel);
        this->Controls->Add(accessLevelLabel); // Добавляем новый Label на форму
        this->Controls->Add(pictureBox);
    }
};
public ref class EmployeeInfoForm : public Form
{
public:
    EmployeeInfoForm()
    {
        InitializeComponent();
    }
    bool IsConfirmed;
    property System::String^ SelectedImagePath;
    System::Windows::Forms::Label^ label1;
    System::Windows::Forms::Label^ label2;
    System::Windows::Forms::Label^ label3;
    System::Windows::Forms::Label^ label4;
    System::Windows::Forms::Label^ label5;
    System::Windows::Forms::Panel^ AccessLevelPanel;
    System::Windows::Forms::NumericUpDown^ AccessLevelNumericUpDown;
    System::Windows::Forms::TextBox^ LevelTextBox;
    System::Windows::Forms::TextBox^ FullNameTextBox;
    System::Windows::Forms::TextBox^ DepartmentTextBox;
    System::Windows::Forms::TextBox^ PositionTextBox;
    System::Windows::Forms::TextBox^ PhoneNumberTextBox;
    System::Windows::Forms::Button^ SelectImageButton;
    System::Windows::Forms::Button^ ConfirmButton;
    System::Windows::Forms::OpenFileDialog^ openFileDialog;
private:

    void InitializeComponent()
    {
        //setting form
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
        this->MaximizeBox = false;
        //
        // level asset label
        // 
        this->label5 = (gcnew System::Windows::Forms::Label());
        this->label5->AutoSize = true;
        this->label5->Location = System::Drawing::Point(5, 118);
        this->label5->Name = L"label5";
        this->label5->Size = System::Drawing::Size(34, 13);
        this->label5->TabIndex = 0;
        this->label5->Text = L"AL:";

        // Добавляем label5 на форму
        this->Controls->Add(this->label5);
        //
        this->AccessLevelPanel = (gcnew System::Windows::Forms::Panel());
        this->AccessLevelPanel->Location = System::Drawing::Point(30, 116); 
        this->AccessLevelPanel->Size = System::Drawing::Size(40, 23);
        this->Controls->Add(this->AccessLevelPanel);
        // 
        this->AccessLevelNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
        this->AccessLevelNumericUpDown->Location = System::Drawing::Point(0, 0);
        this->AccessLevelNumericUpDown->Size = System::Drawing::Size(40, 23);
        this->AccessLevelNumericUpDown->Minimum = 1;
        this->AccessLevelNumericUpDown->Maximum = 5;
        this->AccessLevelPanel->Controls->Add(this->AccessLevelNumericUpDown);
        // 
        //confirmbutton
        this->ConfirmButton = (gcnew System::Windows::Forms::Button());
        this->ConfirmButton->Location = System::Drawing::Point(210, 116);
        this->ConfirmButton->Name = L"ConfirmButton";
        this->ConfirmButton->Size = System::Drawing::Size(120, 23);
        this->ConfirmButton->TabIndex = 9;
        this->ConfirmButton->Text = L"Подтвердить";
        this->ConfirmButton->UseVisualStyleBackColor = true;
        this->ConfirmButton->Click += gcnew System::EventHandler(this, &EmployeeInfoForm::ConfirmButton_Click);
        this->Controls->Add(this->ConfirmButton);

        this->label1 = (gcnew System::Windows::Forms::Label());
        this->label2 = (gcnew System::Windows::Forms::Label());
        this->label3 = (gcnew System::Windows::Forms::Label());
        this->label4 = (gcnew System::Windows::Forms::Label());
        this->FullNameTextBox = (gcnew System::Windows::Forms::TextBox());
        this->DepartmentTextBox = (gcnew System::Windows::Forms::TextBox());
        this->PositionTextBox = (gcnew System::Windows::Forms::TextBox());
        this->PhoneNumberTextBox = (gcnew System::Windows::Forms::TextBox());
        this->SelectImageButton = (gcnew System::Windows::Forms::Button());
        this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
        this->SuspendLayout();
        // 
        // label1
        // 
        this->label1->AutoSize = true;
        this->label1->Location = System::Drawing::Point(12, 15);
        this->label1->Name = L"label1";
        this->label1->Size = System::Drawing::Size(34, 13);
        this->label1->TabIndex = 0;
        this->label1->Text = L"ФИО:";
        // 
        // label2
        // 
        this->label2->AutoSize = true;
        this->label2->Location = System::Drawing::Point(12, 41);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(37, 13);
        this->label2->TabIndex = 1;
        this->label2->Text = L"Отдел:";
        // 
        // label3
        // 
        this->label3->AutoSize = true;
        this->label3->Location = System::Drawing::Point(12, 67);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(68, 13);
        this->label3->TabIndex = 2;
        this->label3->Text = L"Должность:";;
        // 
        // label4
        // 
        this->label4->AutoSize = true;
        this->label4->Location = System::Drawing::Point(12, 93);
        this->label4->Name = L"label4";
        this->label4->Size = System::Drawing::Size(108, 13);
        this->label4->TabIndex = 3;
        this->label4->Text = L"Номер телефона:";
        // 
        // FullNameTextBox
        // 
        this->FullNameTextBox->Location = System::Drawing::Point(126, 12);
        this->FullNameTextBox->Name = L"FullNameTextBox";
        this->FullNameTextBox->Size = System::Drawing::Size(200, 20);
        this->FullNameTextBox->TabIndex = 4;
        // 
        // DepartmentTextBox
        // 
        this->DepartmentTextBox->Location = System::Drawing::Point(126, 38);
        this->DepartmentTextBox->Name = L"DepartmentTextBox";
        this->DepartmentTextBox->Size = System::Drawing::Size(200, 20);
        this->DepartmentTextBox->TabIndex = 5;
        // 
        // PositionTextBox
        // 
        this->PositionTextBox->Location = System::Drawing::Point(126, 64);
        this->PositionTextBox->Name = L"PositionTextBox";
        this->PositionTextBox->Size = System::Drawing::Size(200, 20);
        this->PositionTextBox->TabIndex = 6;
        // 
        // PhoneNumberTextBox
        // 
        this->PhoneNumberTextBox->Location = System::Drawing::Point(126, 90);
        this->PhoneNumberTextBox->Name = L"PhoneNumberTextBox";
        this->PhoneNumberTextBox->Size = System::Drawing::Size(200, 20);
        this->PhoneNumberTextBox->TabIndex = 7;
        // 
        // SelectImageButton
        // 
        this->SelectImageButton->Location = System::Drawing::Point(90,116);
        this->SelectImageButton->Name = L"SelectImageButton";
        this->SelectImageButton->Size = System::Drawing::Size(120, 23);
        this->SelectImageButton->TabIndex = 8;
        this->SelectImageButton->Text = L"Выбрать изображение";
        this->SelectImageButton->UseVisualStyleBackColor = true;
        this->SelectImageButton->Click += gcnew System::EventHandler(this, &EmployeeInfoForm::SelectImageButton_Click);
        // 
        // openFileDialog
        // 
        this->openFileDialog->FileName = L"openFileDialog1";
        // 
        // EmployeeInfoForm
        // 
        this->AcceptButton = this->SelectImageButton;
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(338, 151);
        this->Controls->Add(this->SelectImageButton);
        this->Controls->Add(this->PhoneNumberTextBox);
        this->Controls->Add(this->PositionTextBox);
        this->Controls->Add(this->DepartmentTextBox);
        this->Controls->Add(this->FullNameTextBox);
        this->Controls->Add(this->label4);
        this->Controls->Add(this->label3);
        this->Controls->Add(this->label2);
        this->Controls->Add(this->label1);
        this->Name = L"EmployeeInfoForm";
        this->Text = L"Информация о сотруднике";
        this->ResumeLayout(false);
        this->PerformLayout();

    }
    System::Void EmployeeInfoForm::SetSelectedImagePath(String^ imagePath)
    {
        // Устанавливаем SelectedImagePath после получения пути к изображению
        SelectedImagePath = imagePath;
    }
    delegate void OpenFileDialogDelegate();

    System::Void EmployeeInfoForm::SelectImageButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        System::Threading::Thread^ thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &EmployeeInfoForm::OpenImageFileDialog));
        thread->SetApartmentState(System::Threading::ApartmentState::STA);
        thread->Start();
    }

    System::Void EmployeeInfoForm::OpenImageFileDialog()
    {
        // Открываем диалоговое окно выбора файла для изображения
        openFileDialog->Filter = "Image Files (*.bmp;*.jpg;*.png;*.gif)|*.bmp;*.jpg;*.png;*.gif|All files (*.*)|*.*";
        openFileDialog->FilterIndex = 1;
        openFileDialog->RestoreDirectory = true;

        if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            // Получаем путь к выбранному изображению
            SelectedImagePath = openFileDialog->FileName;
        }
    }

    System::String^ ReadPathFromXmlforSearch();
    System::Void ConfirmButton_Click(System::Object^ sender, System::EventArgs^ e);
};
public ref class ViewAllEmployeesForm : public System::Windows::Forms::Form
{
public:
    ViewAllEmployeesForm(String^ directoryPath)
    {
        InitializeComponent();

        // Заполняем список сотрудников при загрузке формы
        PopulateEmployeeList(directoryPath);
    }

private:
    System::Windows::Forms::ListBox^ employeeListBox;

    void InitializeComponent()
    {
        // Инициализация компонентов формы
        this->employeeListBox = (gcnew System::Windows::Forms::ListBox());
        this->SuspendLayout();

        // 
        // employeeListBox
        // 
        this->employeeListBox->FormattingEnabled = true;
        this->employeeListBox->Location = System::Drawing::Point(12, 12);
        this->employeeListBox->Name = L"employeeListBox";
        this->employeeListBox->Size = System::Drawing::Size(300, 250);
        this->employeeListBox->TabIndex = 0;

        // 
        // ViewAllEmployeesForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(324, 274);
        this->Controls->Add(this->employeeListBox);
        this->Name = L"ViewAllEmployeesForm";
        this->Text = L"Список всех сотрудников";
        this->ResumeLayout(false);
    }
    void PopulateEmployeeList(String^ directoryPath)
    {
        // Очищаем список перед заполнением
        employeeListBox->Items->Clear();

        // Получаем список всех папок (сотрудников) в указанной директории
        std::vector<std::string> employeeFolders;

        // Получаем все папки в указанной директории
        DirectoryInfo^ di = gcnew DirectoryInfo(directoryPath);
        for each (DirectoryInfo ^ subDir in di->GetDirectories())
        {
            // Преобразуем имя папки (сотрудника) в строку
            std::string folderName = msclr::interop::marshal_as<std::string>(subDir->Name);

            // Удаляем первые четыре символа из имени папки
            if (folderName.length() > 4) {
                folderName = folderName.substr(4);
            }
            else {
                folderName = "";
            }

            // Добавляем очищенное имя в вектор
            employeeFolders.push_back(folderName);
        }

        // Добавляем каждого сотрудника в список
        for each (std::string employeeFolder in employeeFolders)
        {
            // Преобразуем строку обратно в System::String^ и добавляем в список
            employeeListBox->Items->Add(gcnew System::String(employeeFolder.c_str()));
        }
    }
};
System::String^ EmployeeInfoForm::ReadPathFromXmlforSearch()
{
    try
    {
        String^ xmlFilePath = "settings.xml";

        if (System::IO::File::Exists(xmlFilePath))
        {
            XmlDocument^ doc = gcnew XmlDocument();
            doc->Load(xmlFilePath);
            XmlNode^ pathNode = doc->SelectSingleNode("/Settings/Path");

            if (pathNode != nullptr)
            {
                String^ pathValue = pathNode->InnerText;
                return pathValue;
            }
            else
            {
                throw gcnew System::Exception("Error: Path node not found in XML");
            }
        }
        else
        {
            throw gcnew System::Exception("Error: XML file not found");
        }
    }
    catch (Exception^ ex)
    {
        Console::WriteLine(ex->Message);
        throw;
    }
}
System::String^ DataBase1::MyForm::ReadPathFromXml()
{
    try
    {
        String^ xmlFilePath = "settings.xml";

        if (System::IO::File::Exists(xmlFilePath))
        {
            XmlDocument^ doc = gcnew XmlDocument();
            doc->Load(xmlFilePath);
            XmlNode^ pathNode = doc->SelectSingleNode("/Settings/Path");

            if (pathNode != nullptr)
            {
                String^ pathValue = pathNode->InnerText;
                return pathValue;
            }
            else
            {
                throw gcnew System::Exception("Error: Path node not found in XML");
            }
        }
        else
        {
            throw gcnew System::Exception("Error: XML file not found");
        }
    }
    catch (Exception^ ex)
    {
        Console::WriteLine(ex->Message);
        throw;
    }
}
System::Void DataBase1::MyForm::SavePathToXml(String^ selectedFolder)
{
    String^ xmlFilePath = Path::Combine(selectedFolder, "settings.xml");

    // Создаем новый XML-документ
    XmlDocument^ doc = gcnew XmlDocument();

    // Создаем корневой элемент "Settings", если файла XML не существует
    if (!System::IO::File::Exists(xmlFilePath))
    {
        XmlElement^ root = doc->CreateElement("Settings");
        doc->AppendChild(root);
    }

    // Создаем элемент "Path" и сохраняем в него выбранный путь
    XmlElement^ pathElement = doc->CreateElement("Path");
    pathElement->InnerText = selectedFolder;
    doc->DocumentElement->AppendChild(pathElement);

    // Сохраняем XML-документ в файл
    doc->Save(xmlFilePath);
}
System::Void DataBase1::MyForm::FButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    PickMainFolder->Description = "Выберите папку работников.";
    PickMainFolder->ShowNewFolderButton = false;
    System::Threading::Thread^ thread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MyForm::ShowFolderDialogInThread));
    thread->SetApartmentState(System::Threading::ApartmentState::STA);
    thread->Start();
}
bool IsValidFolderName(String^ folderName)
{
    for (int i = 0; i < folderName->Length - 2; i++)
    {
        if (folderName[i] == 'A' && folderName[i + 1] == 'L')
        {
            if (Char::IsDigit(folderName[i + 2]) && folderName[i + 2] >= '1' && folderName[i + 2] <= '5')
            {
                return false; // Найдена подстрока вида ALN, где N - цифра от 1 до 5
            }
        }
    }
    return true; // Нет подстрок вида ALN, где N - цифра от 1 до 5
}
System::Void DataBase1::MyForm::FindAndDisplayInfo(String^ directoryPath, String^ targetFolderName)
{
    try
    {
        // Проверяем, что введенная строка содержит более трех символов
        if (targetFolderName->Length <= 3)
        {
            MessageBox::Show("Введите более трех символов для поиска", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Получаем путь к исполняемому файлу
        String^ exeFilePath = Application::ExecutablePath;

        // Извлекаем директорию, в которой находится исполняемый файл
        String^ exeDirectory = Path::GetDirectoryName(exeFilePath);

        // Путь к файлу XML с данными о сотрудниках
        String^ xmlFilePath = Path::Combine(exeDirectory, "settings.xml");

        // Проверяем наличие файла XML
        if (!File::Exists(xmlFilePath))
        {
            MessageBox::Show(xmlFilePath, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Читаем путь к папке из XML файла
        String^ targetFolderPath = ReadPathFromXml();

        // Поиск и отображение информации о сотруднике
        for each (String ^ subdirectory in Directory::GetDirectories(targetFolderPath, "*", SearchOption::AllDirectories))
        {
            String^ folderName = Path::GetFileName(subdirectory);

            // Ищем индекс подстроки "AL" в имени подкаталога
            int index = folderName->IndexOf("AL");
            int accessLevel = 0;

            // Если "AL" найдено в имени подкаталога и символ после "AL" - это цифра от 1 до 5
            if (index != -1 && index + 3 < folderName->Length && folderName[index + 2] == 'N' && Char::IsDigit(folderName[index + 3]) && folderName[index + 3] >= '1' && folderName[index + 3] <= '5')
            {
                // Извлекаем число после "AL" и преобразуем его в число
                String^ accessLevelStr = folderName->Substring(index + 3, 1);
                accessLevel = System::Convert::ToInt32(accessLevelStr);
            }

            // Проверяем соответствие имени папки
            if (folderName->Contains(targetFolderName))
            {
                // Получаем путь к файлу с информацией
                String^ filePath = Path::Combine(subdirectory, "data.txt");

                if (File::Exists(filePath))
                {
                    // Читаем информацию из файла
                    StreamReader^ reader = gcnew StreamReader(filePath);

                    // Читаем строки из файла
                    String^ fio = reader->ReadLine();
                    String^ department = reader->ReadLine();
                    String^ position = reader->ReadLine();
                    String^ phoneNumber = reader->ReadLine();

                    // Закрываем читатель
                    reader->Close();

                    // Формируем строку для отображения, включая уровень доступа
                    String^ infoString = String::Format("ФИО: {0}\nОтдел: {1}\nДолжность: {2}\nНомер телефона: {3}\nУровень доступа: {4}\n",
                        fio, department, position, phoneNumber, accessLevel);

                    // Загружаем и отображаем изображение, если оно существует
                    String^ photoPath = Path::Combine(subdirectory, "photo.jpg");
                    if (File::Exists(photoPath))
                    {
                        // Создаем и отображаем форму с информацией и изображением
                        InfoAndPictureForm^ infoAndPictureForm = gcnew InfoAndPictureForm(infoString, photoPath, accessLevel);
                        infoAndPictureForm->Show();
                    }
                    else
                    {
                        // Если изображение не найдено, создаем форму только с информацией
                        InfoAndPictureForm^ infoAndPictureForm = gcnew InfoAndPictureForm(infoString, "", accessLevel);
                        infoAndPictureForm->Show();
                    }

                    return;
                }
            }
        }
        MessageBox::Show("Информация не найдена", "Поиск", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::NameFind_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        // Получаем путь к исполняемому файлу
        String^ exeFilePath = Application::ExecutablePath;

        // Извлекаем директорию, в которой находится исполняемый файл
        String^ exeDirectory = Path::GetDirectoryName(exeFilePath);

        // Составляем путь к файлу settings.xml в папке с исполняемым файлом
        String^ xmlFilePath = Path::Combine(exeDirectory, "settings.xml");

        // Проверяем наличие файла XML
        if (!File::Exists(xmlFilePath))
        {
            MessageBox::Show(xmlFilePath, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // Если файл XML существует, продолжаем выполнение операции
        String^ directoryPath = ReadPathFromXml();
        String^ targetFolderName = TextName->Text;

        FindAndDisplayInfo(directoryPath, targetFolderName);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::DeleteButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        String^ directoryPath = ReadPathFromXml();
        String^ employeeName = TextBoxFind->Text;

        // Проходим по всем возможным уровням доступа (1-5)
        for (int accessLevel = 1; accessLevel <= 5; accessLevel++)
        {
            // Формируем имя папки сотрудника
            String^ employeeFolderPath = String::Format("AL{0}_{1}", accessLevel, employeeName);

            // Получаем полный путь к папке сотрудника
            String^ fullFolderPath = Path::Combine(directoryPath, employeeFolderPath);

            // Проверяем существование папки сотрудника
            if (Directory::Exists(fullFolderPath))
            {
                // Удаляем папку
                Directory::Delete(fullFolderPath, true);
                MessageBox::Show("Работник успешно удален", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return; // Выходим из метода после удаления папки
            }
        }

        // Если папка сотрудника не найдена
        MessageBox::Show("Работник с таким ФИО не найден", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::ShowFolderDialogInThread()
{
    try
    {
        System::Windows::Forms::DialogResult result = PickMainFolder->ShowDialog();

        if (result == System::Windows::Forms::DialogResult::OK) {
            String^ selectedFolder = PickMainFolder->SelectedPath;

            // Используем Invoke, чтобы обновить UI из потока
            this->Invoke(gcnew Action<String^>(this, &MyForm::UpdateUIAfterFolderSelection), selectedFolder);
        }
        else {
            MessageBox::Show("Ошибка при выборе папки.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    catch (Exception^ ex)
    {
        // Обработка ошибок
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::UpdateUIAfterFolderSelection(String^ selectedFolder)
{
    folderSelected = true;

    // Получаем путь к папке, из которой запущен проект
    String^ projectFolderPath = Path::GetDirectoryName(Application::ExecutablePath);

    // Путь к XML файлу в этой папке
    String^ xmlFilePath = Path::Combine(projectFolderPath, "settings.xml");

    // Читаем существующий XML файл, если он существует
    XmlDocument^ doc = gcnew XmlDocument();

    if (System::IO::File::Exists(xmlFilePath))
    {
        doc->Load(xmlFilePath);
    }
    else
    {
        // Если файл не существует, создаем новый XML документ
        XmlElement^ root = doc->CreateElement("Settings");
        doc->AppendChild(root);
    }

    // Обновляем или добавляем элемент "Path"
    XmlNode^ pathNode = doc->SelectSingleNode("/Settings/Path");
    if (pathNode != nullptr)
    {
        pathNode->InnerText = selectedFolder;
    }
    else
    {
        XmlElement^ pathElement = doc->CreateElement("Path");
        pathElement->InnerText = selectedFolder;
        doc->DocumentElement->AppendChild(pathElement);
    }

    // Сохраняем изменения в XML файл
    doc->Save(xmlFilePath);

    // Используем Invoke, чтобы обновить свойства FButton из потока UI
    this->Invoke(gcnew Action(this, &MyForm::UpdateFButtonVisibility));
}
System::Void DataBase1::MyForm::UpdateFButtonVisibility()
{
    // Сделайте кнопку невидимой
    FButton->Visible = false;
}
System::Void DataBase1::MyForm::AddButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    EmployeeInfoForm^ employeeInfoForm = gcnew EmployeeInfoForm();
    if (employeeInfoForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        if (employeeInfoForm->IsConfirmed)
        {
            String^ fullName = employeeInfoForm->FullNameTextBox->Text;
            String^ department = employeeInfoForm->DepartmentTextBox->Text;
            String^ position = employeeInfoForm->PositionTextBox->Text;
            String^ phoneNumber = employeeInfoForm->PhoneNumberTextBox->Text;
            int accessLevel = (int)employeeInfoForm->AccessLevelNumericUpDown->Value;
            String^ directoryPath = ReadPathFromXml();
            String^ employeeFolderPath = Path::Combine(directoryPath, String::Format("AL{0}_{1}", accessLevel, fullName));
            Directory::CreateDirectory(employeeFolderPath);
            String^ imagePath = employeeInfoForm->SelectedImagePath;
            if (!String::IsNullOrEmpty(imagePath))
            {
                String^ destinationImagePath = Path::Combine(employeeFolderPath, "photo.jpg");
                File::Copy(imagePath, destinationImagePath);
            }
            String^ infoFilePath = Path::Combine(employeeFolderPath, "data.txt");
            StreamWriter^ writer = gcnew StreamWriter(infoFilePath);
            writer->WriteLine(fullName);
            writer->WriteLine(department);
            writer->WriteLine(position);
            writer->WriteLine(phoneNumber);

            writer->Close();

            MessageBox::Show("Новый сотрудник успешно добавлен", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
}
System::Void DataBase1::MyForm::FindInBase_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        // Получаем путь к папке с сотрудниками из XML файла
        String^ directoryPath = ReadPathFromXml();

        // Создаем и отображаем форму со списком сотрудников
        ViewAllEmployeesForm^ employeesForm = gcnew ViewAllEmployeesForm(directoryPath);
        employeesForm->Show();
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void EmployeeInfoForm::ConfirmButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    IsConfirmed = true;
    if (FullNameTextBox->Text->Length < 4)
    {
        MessageBox::Show("ФИО должно содержать не менее 4 символов", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }
    this->DialogResult = System::Windows::Forms::DialogResult::OK;
    this->Close();
}