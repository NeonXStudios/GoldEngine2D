#pragma once
class UIDrawer
{
	virtual void start () = 0;
	virtual void draw  () = 0;
	virtual void update() = 0;
	virtual void lateupdate() = 0;
	virtual void fixupdate() = 0;
};