#if !defined(VUE_H)
#define VUE_H

class Vue {
public:
    static void entree_int_safe(int &entree);

    static void print_menu();

    static bool get_quitter() { return quitter; }

    static void set_quitter(bool q) { quitter = q; }

    static void print_error();

    static void afficher_donnees();

protected:
    static bool quitter;
};
#endif
