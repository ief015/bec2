#pragma once

class SatVisSelection;

class SatVisSelectionHandler
{
protected:
	friend SatVisSelection;

	virtual void onSatVisChanged(SatVisSelection* self) { }
};
