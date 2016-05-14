function createCar() {
	var oTempCar = new Object;
	oTempCar.color = "blue";
	oTempCar.doors = 4;
	oTempCar.mpg = 25;
	oTempCar.showColor = function() {
		alert(this.color);
	};
	
	return oTempCar;
}