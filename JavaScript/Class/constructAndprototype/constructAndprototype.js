function Car(sColor, iDoors, iMpg) {
	this.color = sColor;
	this.doors = iDoors;
	this.mpg = iMpg;
	this.drivers = new Array("Mike", "John");
}


Car.prototype.showColor = function() {
	alert(this.color);
};