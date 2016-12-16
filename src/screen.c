struct update_ins
{
    char ppu_addr_h;
    char ppu_addr_l;
    char ppu_data;
};

static struct update_ins update_buffer_0[30]; // 30 éléments : On ne peux en gérer plus pendant un VBlank
static int size_0;

#define NAME_UPD_ADR (struct update_ins**)0x12
#define NAME_UPD_LEN (unsigned char*)0x14

void init()
{
    (*NAME_UPD_ADR) = update_buffer_0; // Indique à la procédure NMI où se trouve le buffer d'update
    (*NAME_UPD_LEN) = 0;
    size_0=0;
}

void apply_changes()
{
    // Notifier la procédure NMI qu'il y a des updates à faire.
    // Pour cela, on charge le nombre d'updates dans NAME_UDP_LEN
    (*NAME_UPD_LEN) = size_0;
}

void add_change(char l, char c, char data)
{
    
}

void update()
{
    // Si NMI a lu les données, cette case mémoire contient un 0.
    // Donc on oublie exprès les données en question.
    if ((*NAME_UPD_LEN) == 0)
        size_0 = 0;
}
