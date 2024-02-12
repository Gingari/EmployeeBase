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
        pictureBox->SizeMode = PictureBoxSizeMode::Zoom;  // ����������� ����������� �� ��� �����
        pictureBox->Dock = DockStyle::Fill;  // ��������� ��� ��������� ������� �����

        this->Controls->Add(pictureBox);
    }
};
public ref class InfoAndPictureForm : public Form
{
private:
    Label^ infoLabel;
    PictureBox^ pictureBox;
    Label^ accessLevelLabel; // ��������� ����� Label ��� ����������� ������ �������

public:
    InfoAndPictureForm(String^ info, String^ imagePath, int accessLevel)
    {
        // ������������� ����������� �����
        InitializeComponent();

        // ��������� ������ ��� Label
        infoLabel->Text = info;

        // ��������� ������ ��� Label � ������� �������
        accessLevelLabel->Text = "������� �������: " + accessLevel.ToString();

        // �������� � ����������� ����������� � PictureBox
        if (File::Exists(imagePath))
        {
            pictureBox->Image = Image::FromFile(imagePath);
            pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
        }
    }

private:
    void InitializeComponent()
    {
        // �������� ����������� �����
        infoLabel = gcnew Label();
        pictureBox = gcnew PictureBox();
        accessLevelLabel = gcnew Label(); // ������������� ������ Label

        // ��������� �����
        this->Text = "���������� � �����������";
        this->Size = System::Drawing::Size(600, 450); // ����������� ������ ��� ������ Label

        // ��������� Label
        infoLabel->AutoSize = true;
        infoLabel->Location = Point(10, 10);

        // ��������� Label � ������� �������
        accessLevelLabel->AutoSize = true;
        accessLevelLabel->Location = Point(10, 320); // ����������� ��� ������������

        // ��������� PictureBox
        pictureBox->Location = Point(10, 40);
        pictureBox->Size = System::Drawing::Size(500, 270); // ��������� ������ �����������

        // ���������� ����������� �� �����
        this->Controls->Add(infoLabel);
        this->Controls->Add(accessLevelLabel); // ��������� ����� Label �� �����
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

        // ��������� label5 �� �����
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
        this->ConfirmButton->Text = L"�����������";
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
        this->label1->Text = L"���:";
        // 
        // label2
        // 
        this->label2->AutoSize = true;
        this->label2->Location = System::Drawing::Point(12, 41);
        this->label2->Name = L"label2";
        this->label2->Size = System::Drawing::Size(37, 13);
        this->label2->TabIndex = 1;
        this->label2->Text = L"�����:";
        // 
        // label3
        // 
        this->label3->AutoSize = true;
        this->label3->Location = System::Drawing::Point(12, 67);
        this->label3->Name = L"label3";
        this->label3->Size = System::Drawing::Size(68, 13);
        this->label3->TabIndex = 2;
        this->label3->Text = L"���������:";;
        // 
        // label4
        // 
        this->label4->AutoSize = true;
        this->label4->Location = System::Drawing::Point(12, 93);
        this->label4->Name = L"label4";
        this->label4->Size = System::Drawing::Size(108, 13);
        this->label4->TabIndex = 3;
        this->label4->Text = L"����� ��������:";
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
        this->SelectImageButton->Text = L"������� �����������";
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
        this->Text = L"���������� � ����������";
        this->ResumeLayout(false);
        this->PerformLayout();

    }
    System::Void EmployeeInfoForm::SetSelectedImagePath(String^ imagePath)
    {
        // ������������� SelectedImagePath ����� ��������� ���� � �����������
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
        // ��������� ���������� ���� ������ ����� ��� �����������
        openFileDialog->Filter = "Image Files (*.bmp;*.jpg;*.png;*.gif)|*.bmp;*.jpg;*.png;*.gif|All files (*.*)|*.*";
        openFileDialog->FilterIndex = 1;
        openFileDialog->RestoreDirectory = true;

        if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            // �������� ���� � ���������� �����������
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

        // ��������� ������ ����������� ��� �������� �����
        PopulateEmployeeList(directoryPath);
    }

private:
    System::Windows::Forms::ListBox^ employeeListBox;

    void InitializeComponent()
    {
        // ������������� ����������� �����
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
        this->Text = L"������ ���� �����������";
        this->ResumeLayout(false);
    }
    void PopulateEmployeeList(String^ directoryPath)
    {
        // ������� ������ ����� �����������
        employeeListBox->Items->Clear();

        // �������� ������ ���� ����� (�����������) � ��������� ����������
        std::vector<std::string> employeeFolders;

        // �������� ��� ����� � ��������� ����������
        DirectoryInfo^ di = gcnew DirectoryInfo(directoryPath);
        for each (DirectoryInfo ^ subDir in di->GetDirectories())
        {
            // ����������� ��� ����� (����������) � ������
            std::string folderName = msclr::interop::marshal_as<std::string>(subDir->Name);

            // ������� ������ ������ ������� �� ����� �����
            if (folderName.length() > 4) {
                folderName = folderName.substr(4);
            }
            else {
                folderName = "";
            }

            // ��������� ��������� ��� � ������
            employeeFolders.push_back(folderName);
        }

        // ��������� ������� ���������� � ������
        for each (std::string employeeFolder in employeeFolders)
        {
            // ����������� ������ ������� � System::String^ � ��������� � ������
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

    // ������� ����� XML-��������
    XmlDocument^ doc = gcnew XmlDocument();

    // ������� �������� ������� "Settings", ���� ����� XML �� ����������
    if (!System::IO::File::Exists(xmlFilePath))
    {
        XmlElement^ root = doc->CreateElement("Settings");
        doc->AppendChild(root);
    }

    // ������� ������� "Path" � ��������� � ���� ��������� ����
    XmlElement^ pathElement = doc->CreateElement("Path");
    pathElement->InnerText = selectedFolder;
    doc->DocumentElement->AppendChild(pathElement);

    // ��������� XML-�������� � ����
    doc->Save(xmlFilePath);
}
System::Void DataBase1::MyForm::FButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    PickMainFolder->Description = "�������� ����� ����������.";
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
                return false; // ������� ��������� ���� ALN, ��� N - ����� �� 1 �� 5
            }
        }
    }
    return true; // ��� �������� ���� ALN, ��� N - ����� �� 1 �� 5
}
System::Void DataBase1::MyForm::FindAndDisplayInfo(String^ directoryPath, String^ targetFolderName)
{
    try
    {
        // ���������, ��� ��������� ������ �������� ����� ���� ��������
        if (targetFolderName->Length <= 3)
        {
            MessageBox::Show("������� ����� ���� �������� ��� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // �������� ���� � ������������ �����
        String^ exeFilePath = Application::ExecutablePath;

        // ��������� ����������, � ������� ��������� ����������� ����
        String^ exeDirectory = Path::GetDirectoryName(exeFilePath);

        // ���� � ����� XML � ������� � �����������
        String^ xmlFilePath = Path::Combine(exeDirectory, "settings.xml");

        // ��������� ������� ����� XML
        if (!File::Exists(xmlFilePath))
        {
            MessageBox::Show(xmlFilePath, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // ������ ���� � ����� �� XML �����
        String^ targetFolderPath = ReadPathFromXml();

        // ����� � ����������� ���������� � ����������
        for each (String ^ subdirectory in Directory::GetDirectories(targetFolderPath, "*", SearchOption::AllDirectories))
        {
            String^ folderName = Path::GetFileName(subdirectory);

            // ���� ������ ��������� "AL" � ����� �����������
            int index = folderName->IndexOf("AL");
            int accessLevel = 0;

            // ���� "AL" ������� � ����� ����������� � ������ ����� "AL" - ��� ����� �� 1 �� 5
            if (index != -1 && index + 3 < folderName->Length && folderName[index + 2] == 'N' && Char::IsDigit(folderName[index + 3]) && folderName[index + 3] >= '1' && folderName[index + 3] <= '5')
            {
                // ��������� ����� ����� "AL" � ����������� ��� � �����
                String^ accessLevelStr = folderName->Substring(index + 3, 1);
                accessLevel = System::Convert::ToInt32(accessLevelStr);
            }

            // ��������� ������������ ����� �����
            if (folderName->Contains(targetFolderName))
            {
                // �������� ���� � ����� � �����������
                String^ filePath = Path::Combine(subdirectory, "data.txt");

                if (File::Exists(filePath))
                {
                    // ������ ���������� �� �����
                    StreamReader^ reader = gcnew StreamReader(filePath);

                    // ������ ������ �� �����
                    String^ fio = reader->ReadLine();
                    String^ department = reader->ReadLine();
                    String^ position = reader->ReadLine();
                    String^ phoneNumber = reader->ReadLine();

                    // ��������� ��������
                    reader->Close();

                    // ��������� ������ ��� �����������, ������� ������� �������
                    String^ infoString = String::Format("���: {0}\n�����: {1}\n���������: {2}\n����� ��������: {3}\n������� �������: {4}\n",
                        fio, department, position, phoneNumber, accessLevel);

                    // ��������� � ���������� �����������, ���� ��� ����������
                    String^ photoPath = Path::Combine(subdirectory, "photo.jpg");
                    if (File::Exists(photoPath))
                    {
                        // ������� � ���������� ����� � ����������� � ������������
                        InfoAndPictureForm^ infoAndPictureForm = gcnew InfoAndPictureForm(infoString, photoPath, accessLevel);
                        infoAndPictureForm->Show();
                    }
                    else
                    {
                        // ���� ����������� �� �������, ������� ����� ������ � �����������
                        InfoAndPictureForm^ infoAndPictureForm = gcnew InfoAndPictureForm(infoString, "", accessLevel);
                        infoAndPictureForm->Show();
                    }

                    return;
                }
            }
        }
        MessageBox::Show("���������� �� �������", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::NameFind_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        // �������� ���� � ������������ �����
        String^ exeFilePath = Application::ExecutablePath;

        // ��������� ����������, � ������� ��������� ����������� ����
        String^ exeDirectory = Path::GetDirectoryName(exeFilePath);

        // ���������� ���� � ����� settings.xml � ����� � ����������� ������
        String^ xmlFilePath = Path::Combine(exeDirectory, "settings.xml");

        // ��������� ������� ����� XML
        if (!File::Exists(xmlFilePath))
        {
            MessageBox::Show(xmlFilePath, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        // ���� ���� XML ����������, ���������� ���������� ��������
        String^ directoryPath = ReadPathFromXml();
        String^ targetFolderName = TextName->Text;

        FindAndDisplayInfo(directoryPath, targetFolderName);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::DeleteButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        String^ directoryPath = ReadPathFromXml();
        String^ employeeName = TextBoxFind->Text;

        // �������� �� ���� ��������� ������� ������� (1-5)
        for (int accessLevel = 1; accessLevel <= 5; accessLevel++)
        {
            // ��������� ��� ����� ����������
            String^ employeeFolderPath = String::Format("AL{0}_{1}", accessLevel, employeeName);

            // �������� ������ ���� � ����� ����������
            String^ fullFolderPath = Path::Combine(directoryPath, employeeFolderPath);

            // ��������� ������������� ����� ����������
            if (Directory::Exists(fullFolderPath))
            {
                // ������� �����
                Directory::Delete(fullFolderPath, true);
                MessageBox::Show("�������� ������� ������", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
                return; // ������� �� ������ ����� �������� �����
            }
        }

        // ���� ����� ���������� �� �������
        MessageBox::Show("�������� � ����� ��� �� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::ShowFolderDialogInThread()
{
    try
    {
        System::Windows::Forms::DialogResult result = PickMainFolder->ShowDialog();

        if (result == System::Windows::Forms::DialogResult::OK) {
            String^ selectedFolder = PickMainFolder->SelectedPath;

            // ���������� Invoke, ����� �������� UI �� ������
            this->Invoke(gcnew Action<String^>(this, &MyForm::UpdateUIAfterFolderSelection), selectedFolder);
        }
        else {
            MessageBox::Show("������ ��� ������ �����.", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
    catch (Exception^ ex)
    {
        // ��������� ������
        MessageBox::Show("������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void DataBase1::MyForm::UpdateUIAfterFolderSelection(String^ selectedFolder)
{
    folderSelected = true;

    // �������� ���� � �����, �� ������� ������� ������
    String^ projectFolderPath = Path::GetDirectoryName(Application::ExecutablePath);

    // ���� � XML ����� � ���� �����
    String^ xmlFilePath = Path::Combine(projectFolderPath, "settings.xml");

    // ������ ������������ XML ����, ���� �� ����������
    XmlDocument^ doc = gcnew XmlDocument();

    if (System::IO::File::Exists(xmlFilePath))
    {
        doc->Load(xmlFilePath);
    }
    else
    {
        // ���� ���� �� ����������, ������� ����� XML ��������
        XmlElement^ root = doc->CreateElement("Settings");
        doc->AppendChild(root);
    }

    // ��������� ��� ��������� ������� "Path"
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

    // ��������� ��������� � XML ����
    doc->Save(xmlFilePath);

    // ���������� Invoke, ����� �������� �������� FButton �� ������ UI
    this->Invoke(gcnew Action(this, &MyForm::UpdateFButtonVisibility));
}
System::Void DataBase1::MyForm::UpdateFButtonVisibility()
{
    // �������� ������ ���������
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

            MessageBox::Show("����� ��������� ������� ��������", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }
}
System::Void DataBase1::MyForm::FindInBase_Click(System::Object^ sender, System::EventArgs^ e)
{
    try
    {
        // �������� ���� � ����� � ������������ �� XML �����
        String^ directoryPath = ReadPathFromXml();

        // ������� � ���������� ����� �� ������� �����������
        ViewAllEmployeesForm^ employeesForm = gcnew ViewAllEmployeesForm(directoryPath);
        employeesForm->Show();
    }
    catch (Exception^ ex)
    {
        MessageBox::Show("������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}
System::Void EmployeeInfoForm::ConfirmButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    IsConfirmed = true;
    if (FullNameTextBox->Text->Length < 4)
    {
        MessageBox::Show("��� ������ ��������� �� ����� 4 ��������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }
    this->DialogResult = System::Windows::Forms::DialogResult::OK;
    this->Close();
}