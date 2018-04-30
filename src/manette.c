#define MANETTE_1_3 (unsigned char*)0x4016
#define MANETTE_2_4 (unsigned char*)0x4017

static unsigned char prec_manette_1;
static unsigned char manette_1;

static unsigned char recup_manette_1()
{
	unsigned char res = 0;

	res = (res << 1) + (*MANETTE_1_3 & 0x01);
	res = (res << 1) + (*MANETTE_1_3 & 0x01);
	res = (res << 1) + (*MANETTE_1_3 & 0x01);
	res = (res << 1) + (*MANETTE_1_3 & 0x01);

	res = (res << 1) + (*MANETTE_1_3 & 0x01);
	res = (res << 1) + (*MANETTE_1_3 & 0x01);
	res = (res << 1) + (*MANETTE_1_3 & 0x01);
	res = (res << 1) + (*MANETTE_1_3 & 0x01);

	return res;
}

void update_manettes()
{
	*(MANETTE_1_3) = 1;

	prec_manette_1 = manette_1;
	manette_1 = recup_manette_1();

	*(MANETTE_1_3) = 0;
}

unsigned char nouveau_bouton_presse_manette_1(unsigned char bouton)
{
	return (!(prec_manette_1 & bouton)) && (manette_1 & bouton);
}

unsigned char bouton_presse_manette_1(unsigned char bouton)
{
	return (manette_1 & bouton);
}
