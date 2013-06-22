#pragma once

class HueSelection;

class HueSelectionHandler
{
protected:
	friend HueSelection;

	virtual void onHueChanged(HueSelection* self) { }
};
