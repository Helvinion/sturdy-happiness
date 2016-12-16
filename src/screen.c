struct update_ins
{
    char ppu_addr_h;
    char ppu_addr_l;
    char ppu_data;
};

static struct update_ins update_buffer_0[30]; // 30 �l�ments : On ne peux en g�rer plus pendant un VBlank
static int size_0;

#define NAME_UPD_ADR (struct update_ins**)0x12
#define NAME_UPD_LEN (unsigned char*)0x14

void init()
{
    (*NAME_UPD_ADR) = update_buffer_0; // Indique � la proc�dure NMI o� se trouve le buffer d'update
    (*NAME_UPD_LEN) = 0;
    size_0=0;
}

void apply_changes()
{
    // Notifier la proc�dure NMI qu'il y a des updates � faire.
    // Pour cela, on charge le nombre d'updates dans NAME_UDP_LEN
    (*NAME_UPD_LEN) = size_0;
}

void add_change(char l, char c, char data)
{
    
}

void update()
{
    // Si NMI a lu les donn�es, cette case m�moire contient un 0.
    // Donc on oublie expr�s les donn�es en question.
    if ((*NAME_UPD_LEN) == 0)
        size_0 = 0;
}
