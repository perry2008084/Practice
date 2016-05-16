function showColor() {
	alert(this.color);
}

function createCar(sColor, iDoors, iMpg) {
	var oTempCar = new Object;
	oTempCar.color = sColor;
	oTempCar.doors = iDoors;
	oTempCar.mpg = iMpg;
	oTempCar.showColor = showColor;
	
	return oTempCar;
}