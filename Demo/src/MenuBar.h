#ifndef __MENU_BAR_H__
#define __MENU_BAR_H__

class CodeMenu : public scv::ContextMenu {
public:
   ///////////////////////////////////////////////////////////
   CodeMenu(void);
   virtual ~CodeMenu(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void onMenuAccessed(const std::deque<std::string> &address);
   ///////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class ManagedObjectsMenu : public scv::ContextMenu {
public:
   ///////////////////////////////////////////////////////////
   ManagedObjectsMenu(void);
   virtual ~ManagedObjectsMenu(void);
   ///////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////
   virtual void onMenuAccessed(const std::deque<std::string> &address);
   virtual void onStatusChange(void);
   ///////////////////////////////////////////////////////////
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

class MenuBar : public scv::MenuBar {
public:
   ///////////////////////////////////////////////////////////
   MenuBar(int width);
   virtual ~MenuBar(void);
   ///////////////////////////////////////////////////////////
};

#endif //__MENU_BAR_H__