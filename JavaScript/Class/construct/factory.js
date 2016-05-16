function Car(sColor, iDoors, iMpg) {
	this.color = sColor;
	this.doors = iDoors;
	this.mpg = iMpg;
	this.showColor = function() {
		alert(this.color);
	};
}