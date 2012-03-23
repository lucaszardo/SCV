#include <SCV/SCV.h>
#include "CodeGenerator.h"
#include "Application.h"

CodeGenerator::CodeGenerator(void) {
   _scvFrame = NULL;
}

CodeGenerator::~CodeGenerator(void) {
}

/*recebe os componentes do kernel e insere na managedList, FALTA O SCROLL */
void CodeGenerator::addComponent(scv::Component *comp) {
   scv::Component *object = NULL;
   std::string aditionalString = "";

   deleteComponents();

   if (comp->getType() == 1) { //Panel
      object = new scv::Panel(comp->getRelativePosition(), comp->getSize());
      addManagedComponent(object, "Panel", aditionalString);
      return ;
   } else if (comp->getType() == 2) { //ColorPicker
      object = new scv::ColorPicker(comp->getRelativePosition());
      addManagedComponent(object, "ColorPicker", aditionalString);
      return ;
   } else if (comp->getType() == 3) { //ProgressBar
      object = new scv::ProgressBar(comp->getRelativePosition(),  0);
      addManagedComponent(object, "ProgressBar", aditionalString);
      return ;
   } else if (comp->getType() == 5) {  //Slider
      object = new scv::Slider(comp->getRelativePosition(), comp->getWidth(), 0.f, 100.f, 50.f, 1.f);
      addManagedComponent(object, "Slider", aditionalString);
      return ;
   } else if (comp->getType() == 6) { //Spinner
      object = new scv::Spinner(comp->getRelativePosition(), comp->getWidth(), 0.f, 100.f, 50.f, 1.f);
      addManagedComponent(object, "Spinner", aditionalString);
      return ;
   } else if (comp->getType() == 7) {  //Button
      object = new scv::Button(comp->getRelativePosition(), comp->getSize(), "SCV Button");
      addManagedComponent(object, "Button", aditionalString);
      return ;
      //aditionalString = "_SCV_Button";
   } else if (comp->getType() == 8) {  //CheckBox
      object = new scv::CheckBox(comp->getRelativePosition(), false, "SCV CheckBox");
      addManagedComponent(object, "CheckBox", aditionalString);
      return ;
   } else if (comp->getType() == 9) {  //RadioButton
      object = new scv::RadioButton(comp->getRelativePosition(), false, "SCV RadioButton");
      addManagedComponent(object, "RadioButton", aditionalString);
      return ;
   } else if (comp->getType() == 10) {  //ToggleButton
      object = new scv::ToggleButton(comp->getRelativePosition(), false, "SCV ToogleButton");
      addManagedComponent(object, "ToggleButton", aditionalString);
      return ;
   } else if (comp->getType() == 11) {  //TextField
      object = new scv::TextField(comp->getRelativePosition(), comp->getWidth(), "SCV TextField");
      addManagedComponent(object, "TextField", aditionalString);
      return ;
   } else if (comp->getType() == 12) {  //TextBox
      object = new scv::TextBox(comp->getRelativePosition(), comp->getSize(), "SCV TextBox");
      addManagedComponent(object, "TextBox", aditionalString);
      return ;
   } else if (comp->getType() == 13) {  //Separator
      object = new scv::Separator(comp->getRelativePosition(), scv::Separator::HORIZONTAL, 100);
      addManagedComponent(object, "Separator", aditionalString);
      return ;
   } else if (comp->getType() == 14) {  //InternalFrame
      object = new scv::InternalFrame(200, 200, "SCV InternalFrame");
      addManagedComponent(object, "InternalFrame", aditionalString);
      return ;
   } else if (comp->getType() == 15) {  //MenuBar
      object = new scv::MenuBar(comp->getWidth());
      addManagedComponent(object, "MenuBar", aditionalString);
      return ;
   } else if (comp->getType() == 16) {  //TabbedPane
      object = new scv::TabbedPane(comp->getRelativePosition(), comp->getSize());
      addManagedComponent(object, "TabbedPane", aditionalString);
      return ;
   } else if (comp->getType() == 17) {  //ScrollComponent
      object = new scv::ScrollComponent(comp->getRelativePosition(), comp->getSize());
      addManagedComponent(object, "ScrollComponent", aditionalString);
      return ;
   } else if (comp->getType() == 18) {  //Image
      object = new scv::Image(comp->getRelativePosition(), "default_image.png");
      addManagedComponent(object, "Image", aditionalString);
      return ;
   } else if (comp->getType() == 19) {  //Table
      object = new scv::Table(comp->getRelativePosition(),4,4,1,15);
      addManagedComponent(object, "Table", aditionalString);
      return ;
   } else if (comp->getType() == 20) {  //ComboBox
      object = new scv::ComboBox(comp->getRelativePosition(), comp->getSize());
      addManagedComponent(object, "ComboBox", aditionalString);
      return ;
   } else if (comp->getType() == 21) {  //Canvas
      object = new scv::Canvas(comp->getRelativePosition(), comp->getSize());
      addManagedComponent(object, "Canvas", aditionalString);
      return ;
   /*} else if (comp->getType() == 22) {  //SystemTreeView
      object = new scv::SystemTreeView(comp->getRelativePosition(), comp->getSize());
      addManagedComponent(object, "SystemTreeView", aditionalString);
      return ;*/
   } else if (comp->getType() == 23) {  //Label
      object = new scv::Label(comp->getRelativePosition(), "SCV Label");
      addManagedComponent(object, "Label", aditionalString);
      return ;
   }
}

/*Adiciona novo componente criado no Pallete (A string adicional � para componentes especiais)*/
void CodeGenerator::addManagedComponent(scv::Component *object, const std::string &type, const std::string &aString) {
    _managed.push_back(new ManagedComponent(object, type + scv::toString(getComponentCount(object->getType())) + aString , type));
}

void CodeGenerator::deleteComponent(ManagedComponent *managed) {
   if (std::find(_managed.begin(), _managed.end(), managed) != _managed.end()) {
      _managed.remove(managed);
   }
   delete managed;
}

/**/
void CodeGenerator::deleteComponents()
{
    ManagedComponent* a;
    while(_managed.size() > 1)
    {
        a = _managed.back();
        if(a->getParent() != NULL){
            a->getParent()->removeChild(a);
        }else
        {
            _managed.pop_back();
        }
    }
}

bool CodeGenerator::hasComponent(scv::Component *object) const {
   return getManagedComponent(object) ? true : false;
}

bool CodeGenerator::hasComponent(const std::string &name) const {
   return getManagedComponent(name) ? true : false;
}

ManagedComponent *CodeGenerator::getManagedComponent(scv::Component *object) const {
   for (ManagedList::const_iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == object) {
         return(*iter);
      } else {         
         ManagedComponent *managed = (*iter)->getChild(object);
         if (managed != NULL) return managed;
      }
   }
   return NULL;
}

ManagedComponent *CodeGenerator::getManagedComponent(const std::string &name) const {
   for (ManagedList::const_iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getClassName() == name) {
         return(*iter);
      } else {
         ManagedComponent *managed = (*iter)->getChild(name);
         if (managed != NULL) return managed;
      }
   }
   return NULL; 
}

CodeGenerator::ManagedList CodeGenerator::getManagedComponents(void) const {
   return _managed;
}

std::string CodeGenerator::addChildren(scv::Component *child, std::string dad) {
   std::string code;
   int x, y;
   int type = child->getType();

   if(type == 1) { // Panel
      if(child == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = count[child->getType()];
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Panel *panel" + scv::toString(count_n) + " = new scv::Panel(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      panel" + scv::toString(count_n) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "panel" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 2) { // ColorPicker
      code += "      scv::ColorPicker *colorPicker" + scv::toString(count[child->getType()]) + " = new scv::ColorPicker(scv::Point(" + scv::toString(child->getRelativePosition()) + "));\n";
      code += "      colorPicker" + scv::toString(count[child->getType()]) + "->" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 3) { // ProgressBar
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::ProgressBar *progressBar" + scv::toString(count[child->getType()]) + " = new scv::ProgressBar(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      code += "      progressBar" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 4) { // Scroll

   } else if(type == 5) { // Slider
      code += "      scv::Slider *slider" + scv::toString(count[child->getType()]) + " = new scv::Slider(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "      slider" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 6) { // Spinner
      code += "      scv::Spinner *spinner" + scv::toString(count[child->getType()]) + " = new scv::Spinner(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "      spineer" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 7) { // Button
      scv::Button *button = (scv::Button*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Button *button" + scv::toString(count[child->getType()]) + " = new scv::Button(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      code += "      button" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 8) { // CheckBox
      scv::CheckBox *checkBox = (scv::CheckBox*)(child);
      code += "      scv::CheckBox *checkBox" + scv::toString(count[child->getType()]) + " = new scv::CheckBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      code += "      checkBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 9) { // RadioButton
      scv::RadioButton *radioButton = (scv::RadioButton*)(child);
      code += "      scv::RadioButton *radioButton" + scv::toString(count[child->getType()]) + " = new scv::RadioButton(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      code += "      radioButton" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 10) {// ToggleButton
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      scv::ToggleButton *toggleButton = (scv::ToggleButton*)(child);
      code += "      scv::ToggleButton *toggleButton" + scv::toString(count[child->getType()]) + " = new scv::ToggleButton(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      code += "      toggleButton" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      code += "\n";
   } else if(type == 11) {// TextField
      scv::TextField *textField = (scv::TextField*)(child);
      code += "      scv::TextField *textField" + scv::toString(count[child->getType()]) + " = new scv::TextField(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(child->getWidth()) + ", \"" + textField->getString() + "\");\n";
      code += "      textField" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 12) {// TextBox
      scv::TextBox *textBox = (scv::TextBox*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::TextBox *textBox" + scv::toString(count[child->getType()]) + " = new scv::TextBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + textBox->getString() + "\");\n";
      code += "      textBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 13) {// Separator
      scv::Separator *separator = (scv::Separator*)(child);
      if(separator->getAlign() == 0)
         code += "      scv::Separator *separator" + scv::toString(count[child->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(child->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getWidth()) + ");\n";
      if(separator->getAlign() == 1)
         code += "      scv::Separator *separator" + scv::toString(count[child->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(child->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getHeight()) + ");\n";
      code += "      separator" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 14) {// Window

   } else if(type == 15) {// MenuBar
      code += "      scv::MenuBar *menuBar" + scv::toString(count[child->getType()]) + " = new scv::MenuBar(" + scv::toString(child->getWidth()) + ");\n";
      code += "      menuBar" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 16) {// TabbedPane
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      int count_n = count[child->getType()];
      code += "      scv::TabbedPane *tabbedPane" + scv::toString(count[child->getType()]) + " = new scv::TabbedPane(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      tabbedPane" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "tabbedPane" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 17) {// ScrollComponent
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      int count_n = count[child->getType()];
      code += "      scv::ScrollComponent *scrollComponent" + scv::toString(count[child->getType()]) + " = new scv::ScrollComponent(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      scrollComponent" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "scrollComponent" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 18) {// Image
      scv::Image *image = (scv::Image*)(child);
      int count_n = count[child->getType()];
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Image *image" + scv::toString(count[child->getType()]) + " = new scv::Image(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      code += "      image" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      if(!child->_children.empty()) {
         for(auto c = child->_children.begin(); c != child->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "image" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 19) {//Table
      scv::Table *table = (scv::Table*)(child);
      code += "      scv::Table *table" + scv::toString(count[child->getType()]) + " = new scv::Table(scv::Point(" + scv::toString(child->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      code += "      table" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 20) {//ComboBox
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::ComboBox *comboBox" + scv::toString(count[child->getType()]) + " = new scv::ComboBox(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      comboBox" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 21) {//Canvas
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Canvas *canvas" + scv::toString(count[child->getType()]) + " = new scv::Canvas(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "      canvas" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 22) {//TreeView
      scv::GenericTree *genericTree = (scv::GenericTree*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::GenericTree *genericTree" + scv::toString(count[child->getType()]) + " = new scv::GenericTree(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(genericTree->getRootNode()) + ");\n";
      code += "      genericTree" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   } else if(type == 23) {//Label
      scv::Label *label = (scv::Label*)(child);
      x = child->getRelativePosition().x + child->getWidth();
      y = child->getRelativePosition().y + child->getHeight();
      code += "      scv::Label *label" + scv::toString(count[child->getType()]) + " = new scv::Label(scv::Point(" + scv::toString(child->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      code += "      label" + scv::toString(count[child->getType()]) + "->setParent(" + dad + ");\n";
      count[child->getType()] += 1;
      code += "\n";
   }
   return code;
}

std::string CodeGenerator::createAllocationCode(scv::Component *comp) {
   std::string code;
   int x, y;
   int type = comp->getType();

   if(type == 1) { // Panel
      if(comp == static_cast<Application*>(scv::Kernel::getInstance())->_mainPanel)
         return "";
      int count_n = 0;
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Panel *panel" + scv::toString(count[comp->getType()]) + " = new scv::Panel(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(panel" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "panel" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 2) { // ColorPicker
      code += "   scv::ColorPicker *colorPicker" + scv::toString(count[comp->getType()]) + " = new scv::ColorPicker(scv::Point(" + scv::toString(comp->getRelativePosition()) + "));\n";
      code += "   addComponent(colorPicker" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 3) { // ProgressBar
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::ProgressBar *progressBar" + scv::toString(count[comp->getType()]) + " = new scv::ProgressBar(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + "0);\n";
      code += "   addComponent(progressBar" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 4) { // Scroll

   } else if(type == 5) { // Slider
      code += "   scv::Slider *slider" + scv::toString(count[comp->getType()]) + " = new scv::Slider(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   addComponent(slider" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 6) { // Spinner
      code += "   scv::Spinner *spinner" + scv::toString(count[comp->getType()]) + " = new scv::Spinner(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", 0.f, 100.f, 50.f, 1.f);\n";
      code += "   addComponent(spineer" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 7) { // Button
      scv::Button *button = (scv::Button*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Button *button" + scv::toString(count[comp->getType()]) + " = new scv::Button(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(button->getString()) + "\");\n";
      code += "   addComponent(button" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 8) { // CheckBox
      scv::CheckBox *checkBox = (scv::CheckBox*)(comp);
      code += "   scv::CheckBox *checkBox" + scv::toString(count[comp->getType()]) + " = new scv::CheckBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(checkBox->getState()) + ", \"" + scv::toString(checkBox->getString()) + "\");\n";
      code += "   addComponent(checkBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 9) { // RadioButton
      scv::RadioButton *radioButton = (scv::RadioButton*)(comp);
      code += "   scv::RadioButton *radioButton" + scv::toString(count[comp->getType()]) + " = new scv::RadioButton(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(radioButton->getState()) + ", \"" + scv::toString(radioButton->getString()) + "\");\n";
      code += "   addComponent(radioButton" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 10) {// ToggleButton
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      scv::ToggleButton *toggleButton = (scv::ToggleButton*)(comp);
      code += "   scv::ToggleButton *toggleButton" + scv::toString(count[comp->getType()]) + " = new scv::ToggleButton(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(toggleButton->getState()) + ", \"" + scv::toString(toggleButton->getString()) + "\");\n";
      code += "   addComponent(toggleButton" + scv::toString(count[comp->getType()]) + ");\n";
      code += "\n";
   } else if(type == 11) {// TextField
      scv::TextField *textField = (scv::TextField*)(comp);
      code += "   scv::TextField *textField" + scv::toString(count[comp->getType()]) + " = new scv::TextField(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(comp->getWidth()) + ", \"" + textField->getString() + "\");\n";
      code += "   addComponent(textField" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 12) {// TextBox
      scv::TextBox *textBox = (scv::TextBox*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::TextBox *textBox" + scv::toString(count[comp->getType()]) + " = new scv::TextBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + textBox->getString() + "\");\n";
      code += "   addComponent(textBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 13) {// Separator
      scv::Separator *separator = (scv::Separator*)(comp);
      if(separator->getAlign() == 0)
         code += "   scv::Separator *separator" + scv::toString(count[comp->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getWidth()) + ");\n";
      if(separator->getAlign() == 1)
         code += "   scv::Separator *separator" + scv::toString(count[comp->getType()]) + " = new scv::Separator(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), (scv::Separator::Orientation)" + scv::toString(separator->getAlign()) + ", " + scv::toString(separator->getHeight()) + ");\n";
      code += "   addComponent(separator" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 14) {// Window

   } else if(type == 15) {// MenuBar
      code += "   scv::MenuBar *menuBar" + scv::toString(count[comp->getType()]) + " = new scv::MenuBar(" + scv::toString(comp->getWidth()) + ");\n";
      code += "   addComponent(menuBar" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 16) {// TabbedPane
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      int count_n = count[comp->getType()];
      code += "   scv::TabbedPane *tabbedPane" + scv::toString(count[comp->getType()]) + " = new scv::TabbedPane(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(tabbedPane" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "tabbedPane" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 17) {// ScrollComponent
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      int count_n = count[comp->getType()];
      code += "   scv::ScrollComponent *scrollComponent" + scv::toString(count[comp->getType()]) + " = new scv::ScrollComponent(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(scrollComponent" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "scrollComponent" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 18) {// Image
      scv::Image *image = (scv::Image*)(comp);
      int count_n = count[comp->getType()];
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Image *image" + scv::toString(count[comp->getType()]) + " = new scv::Image(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(image->getPath()) + "\");\n";
      code += "   addComponent(image" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      if(!comp->_children.empty()) {
         for(auto c = comp->_children.begin(); c != comp->_children.end(); c++) {
            scv::Component *a = *c;
            code += addChildren(a, "image" + scv::toString(count_n));
         }
      }
      code += "\n";
   } else if(type == 19) {//Table
      scv::Table *table = (scv::Table*)(comp);
      code += "   scv::Table *table" + scv::toString(count[comp->getType()]) + " = new scv::Table(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), " + scv::toString(table->getNumberOfRows()) + ", " + scv::toString(table->getNumberOfColumns()) + ", " + scv::toString(table->getNumberOfLinesPerCell()) + ", " + scv::toString(table->getCellWidth()) + ");\n";
      code += "   addComponent(table" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 20) {//ComboBox
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::ComboBox *comboBox" + scv::toString(count[comp->getType()]) + " = new scv::ComboBox(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(comboBox" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 21) {//Canvas
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Canvas *canvas" + scv::toString(count[comp->getType()]) + " = new scv::Canvas(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "));\n";
      code += "   addComponent(canvas" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 22) {//TreeView
      scv::GenericTree *genericTree = (scv::GenericTree*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::GenericTree *genericTree" + scv::toString(count[comp->getType()]) + " = new scv::GenericTree(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), " + scv::toString(genericTree->getRootNode()) + ");\n";
      code += "   addComponent(genericTree" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   } else if(type == 23) {//Label
      scv::Label *label = (scv::Label*)(comp);
      x = comp->getRelativePosition().x + comp->getWidth();
      y = comp->getRelativePosition().y + comp->getHeight();
      code += "   scv::Label *label" + scv::toString(count[comp->getType()]) + " = new scv::Label(scv::Point(" + scv::toString(comp->getRelativePosition()) + "), scv::Point(" + scv::toString(x) + ", " + scv::toString(y) + "), \"" + scv::toString(label->getString()) + "\");\n";
      code += "   addComponent(label" + scv::toString(count[comp->getType()]) + ");\n";
      count[comp->getType()] += 1;
      code += "\n";
   }
   return code;
}

void CodeGenerator::generateCode(void) {

   memset(count, 0, sizeof(int)*23);
   // main.cpp
   ///////////////////////////////////////////////////////////
   std::string mainDotCpp, allocationCode;
   mainDotCpp += "#include <SCV/SCV.h>\n";
   mainDotCpp += "#include \"Application.h\"\n";
   mainDotCpp += "\n";
   mainDotCpp += "int main(int argc, char* argv[]) {\n";
   mainDotCpp += "   Application *kernel = new Application();\n";
   mainDotCpp += "   scv::Kernel::setInstance(kernel);\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->init();\n";
   mainDotCpp += "\n";

   for(auto comp = Application::getInstance()->_objects.begin(); comp != Application::getInstance()->_objects.end(); comp++) {
      allocationCode += createAllocationCode(*comp);
   }

   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";
   ///////////////////////////////////////////////////////////

   // Application.h
   ///////////////////////////////////////////////////////////
   std::string applicationDotH;   
   applicationDotH += "#ifndef __APPLICATION_H__\n";
   applicationDotH += "#define __APPLICATION_H__\n";
   applicationDotH += "\n";
   applicationDotH += "#include <SCV/SCV.h>\n";
   applicationDotH += "\n";
   applicationDotH += "class Application : public scv::Kernel {\n";
   applicationDotH += "public:\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   Application(void);\n";
   applicationDotH += "   virtual ~Application(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "   void init(void);\n";
   applicationDotH += "\n";
   applicationDotH += "   //SCVCallbacks\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   virtual void onMouseClick(const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseHold (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseOver (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n";
   applicationDotH += "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onSizeChange(void);\n";
   applicationDotH += "   virtual void onPositionChange(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "protected:\n";
   applicationDotH += "   static const int s_defaultWindowWidth = 1280;\n";
   applicationDotH += "   static const int s_defaultWindowHeight = 720;\n";
   applicationDotH += "   scv::Panel *_mainPanel;\n";
   applicationDotH += "private:\n";
   applicationDotH += "};\n";
   applicationDotH += "\n";
   applicationDotH += "#endif //__APPLICATION_H__\n";
   ///////////////////////////////////////////////////////////

   // Application.cpp
   ///////////////////////////////////////////////////////////
   std::string applicationDotCpp;
   applicationDotCpp += "#include \"Application.h\"\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::Application(void) : Kernel() {\n";
   applicationDotCpp += "   setWindowSize(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + ");\n";
   applicationDotCpp += "   lockWindowSize(false);\n";
   applicationDotCpp += "   setFramesPerSecond(60);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   setWindowTitle(\"SCV Interface Designer v1.1\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + "));\n";
   applicationDotCpp += "\n";
   //applicationDotCpp += static_cast<Application *>(Application::getInstance())->getLayoutCode("_mainPanel") + "\n";
   applicationDotCpp += "   addComponent(_mainPanel);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += allocationCode;
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onMouseClick(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseHold(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseOver(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseUp(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseWheel(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onKeyPressed(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onKeyUp(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onSizeChange(void) {\n";
   applicationDotCpp += "   _mainPanel->setSize(getWidth(), getHeight());\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onPositionChange(void) {\n";
   applicationDotCpp += "}\n";   
   ///////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////
   std::ofstream outputFile;

   outputFile = std::ofstream("../ExportedSource/src/Application.h");
   outputFile << applicationDotH;
   outputFile.close();

   outputFile = std::ofstream("../ExportedSource/src/Application.cpp");
   outputFile << applicationDotCpp;
   outputFile.close();

   outputFile = std::ofstream("../ExportedSource/src/main.cpp");
   outputFile << mainDotCpp;
   outputFile.close();
   ///////////////////////////////////////////////////////////
}

std::string CodeGenerator::generateCodeMain(void)
{
    ///////////////////////////////////////////////////////////
   std::string mainDotCpp;
   mainDotCpp += "#include <SCV/SCV.h>\n";
   mainDotCpp += "#include \"Application.h\"\n";
   mainDotCpp += "\n";
   mainDotCpp += "int main(int argc, char* argv[]) {\n";
   mainDotCpp += "   scv::Kernel *kernel = scv::Kernel::getInstance();\n";
   mainDotCpp += "   scv::Kernel::setInstance(kernel);\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->init();\n";
   mainDotCpp += "\n";
   mainDotCpp += "   kernel->run();\n";
   mainDotCpp += "   return 0;\n";
   mainDotCpp += "}\n";
   ///////////////////////////////////////////////////////////

   return mainDotCpp;
}
std::string CodeGenerator::generateCodeAppH(void)
{
   // Application.h
   ///////////////////////////////////////////////////////////
   std::string applicationDotH;   
   applicationDotH += "#ifndef __APPLICATION_H__\n";
   applicationDotH += "#define __APPLICATION_H__\n";
   applicationDotH += "\n";
   applicationDotH += "#include <SCV/SCV.h>\n";
   applicationDotH += "\n";
   applicationDotH += "class Application : public scv::Kernel {\n";
   applicationDotH += "public:\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   Application(void);\n";
   applicationDotH += "   virtual ~Application(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "   void init(void);\n";
   applicationDotH += "\n";
   applicationDotH += "   //SCVCallbacks\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "   virtual void onMouseClick(const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseHold (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseOver (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseUp   (const scv::MouseEvent &evt);\n";
   applicationDotH += "   virtual void onMouseWheel(const scv::MouseEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onKeyPressed(const scv::KeyEvent &evt);\n";
   applicationDotH += "   virtual void onKeyUp     (const scv::KeyEvent &evt);\n";
   applicationDotH += "\n";
   applicationDotH += "   virtual void onSizeChange(void);\n";
   applicationDotH += "   virtual void onPositionChange(void);\n";
   applicationDotH += "   ///////////////////////////////////////////////////////////\n";
   applicationDotH += "\n";
   applicationDotH += "protected:\n";
   applicationDotH += "   static const int s_defaultWindowWidth = 1280;\n";
   applicationDotH += "   static const int s_defaultWindowHeight = 720;\n";
   applicationDotH += "   scv::Panel *_mainPanel;\n";
   applicationDotH += "private:\n";
   applicationDotH += "};\n";
   applicationDotH += "\n";
   applicationDotH += "#endif //__APPLICATION_H__\n";
   ///////////////////////////////////////////////////////////

   return applicationDotH;

}

std::string CodeGenerator::generateCodeAppCpp(void)
{
   ///////////////////////////////////////////////////////////
   std::string allocationCode;
   for (ManagedList::iterator iter = _managed.begin(); iter != _managed.end(); ++iter) {
      if ((*iter)->getComponent() == _scvFrame) continue;
      allocationCode += (*iter)->getAllocationCode();
   }
   ///////////////////////////////////////////////////////////

   // Application.cpp
   ///////////////////////////////////////////////////////////
   std::string applicationDotCpp;
   applicationDotCpp += "#include \"Application.h\"\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::Application(void) : Kernel() {\n";
   applicationDotCpp += "   setWindowSize(" + scv::toString(Application::getInstance()->getWidth()) + ", " + scv::toString(Application::getInstance()->getHeight()) + ");\n";
   applicationDotCpp += "   lockWindowSize(false);\n";
   applicationDotCpp += "   setFramesPerSecond(60);\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   setWindowTitle(\"SCV Interface Designer v1.1\");\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "Application::~Application(void) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::init(void) {\n";
   applicationDotCpp += "   _mainPanel = new scv::Panel(scv::Point(0, 0), scv::Point(s_defaultWindowWidth, s_defaultWindowHeight));\n";
   applicationDotCpp += allocationCode;
   //applicationDotCpp += static_cast<Application *>(Application::getInstance())->getLayoutCode("_mainPanel") + "\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "   addComponent(_mainPanel);\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onMouseClick(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseHold(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseOver(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseUp(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onMouseWheel(const scv::MouseEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onKeyPressed(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onKeyUp(const scv::KeyEvent &evt) {\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "\n";
   applicationDotCpp += "void Application::onSizeChange(void) {\n";
   applicationDotCpp += "   _mainPanel->setSize(getWidth(), getHeight());\n";
   applicationDotCpp += "}\n";
   applicationDotCpp += "void Application::onPositionChange(void) {\n";
   applicationDotCpp += "}\n";   
   ///////////////////////////////////////////////////////////

   return applicationDotCpp;
}

int CodeGenerator::getComponentCount(scv::Component::Type type) {
   return _counter[type]++;
}

std::string SpacesToUnderlines(std::string s)
{
    for(int i = 0 ; i < s.length() ; i++)
    {
        if(s[i] == ' ')
        {
            s[i] = '_';
        }
    }
    return s;
}

void CodeGenerator::modifyNameManagedComponent(scv::Component *obj, std::string newName)
{
    ManagedComponent *a = getManagedComponent(obj);
    a->setClassName(a->getClassName().substr(0,a->getClassName().find('_')+1) + SpacesToUnderlines(newName));
}

void CodeGenerator::setSCVFrame(scv::InternalFrame *frame) {
   if (_scvFrame == NULL) {
      _scvFrame = frame;
      addManagedComponent(frame, "InternalFrame");
   }
}

