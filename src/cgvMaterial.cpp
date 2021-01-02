#include "cgvMaterial.h"

// Constructor and destructor methods 

cgvMaterial::cgvMaterial() {

}

cgvMaterial::~cgvMaterial() {

}

cgvMaterial::cgvMaterial(const cgvMaterial& m) {	//copy constructor
	Ka = m.Ka;
	Kd = m.Kd;
	Ks = m.Ks;
	Ns = m.Ns;
}

cgvMaterial::cgvMaterial(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}

// Public methods 

void cgvMaterial::apply(void) {

	// Section C
	// Apply the attributes of the cgvMaterial object:
	// - ambient coefficient 
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ka.data());
	// - diffuse coefficient
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Kd.data());
	// - specular coefficient
	glMaterialfv(GL_FRONT, GL_SPECULAR, Ks.data());
	// - Phong exponent
	glMaterialf(GL_FRONT, GL_SHININESS, Ns);
	// set the color (0.0, 0.0, 0.0) as emission color (the object is not a light source )
	glMaterialfv(GL_FRONT, GL_EMISSION, cgvColor4f(0, 0, 0).data());

}

void cgvMaterial::set(cgvColor4f _Ka, cgvColor4f _Kd, cgvColor4f _Ks, double _Ns) {
	Ka = _Ka;
	Kd = _Kd;
	Ks = _Ks;
	Ns = _Ns;
}



