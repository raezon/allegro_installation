#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 32
#define FPS 60

int main()
{
    // Initialisation d'Allegro
    if (!al_init()) {
        al_show_native_message_box(NULL, "Erreur", "Erreur", "Impossible d'initialiser Allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Initialisation des modules Allegro
    al_install_keyboard(); // Clavier
    al_init_primitives_addon(); // Primitives (carrés, cercles, etc.)
    al_init_image_addon(); // Images
    al_init_font_addon(); // Fontes
    al_init_ttf_addon(); // Fontes TTF

    // Crée une fenêtre
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        al_show_native_message_box(NULL, "Erreur", "Erreur", "Impossible de créer une fenêtre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Définir le titre de la fenêtre
    al_set_window_title(display, "Déplacement d'un carré avec Allegro");

    // Création d'une minuterie pour contrôler le FPS
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    // Enregistrement des sources d'événements
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Variables pour la position du carré
    float x = SCREEN_WIDTH / 2.0 - SQUARE_SIZE / 2.0;
    float y = SCREEN_HEIGHT / 2.0 - SQUARE_SIZE / 2.0;
    float speed = 4.0;

    bool do_exit = false;
    bool redraw = true;
    ALLEGRO_KEYBOARD_STATE key_state;

    // Démarrage de la minuterie
    al_start_timer(timer);

    // Boucle de jeu principale
    while (!do_exit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        // Si l'utilisateur ferme la fenêtre
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            do_exit = true;
        }

        // Gérer les événements du clavier
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    do_exit = true; // Sortie du jeu en appuyant sur Echap
                    break;
            }
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            // Obtenir l'état actuel du clavier
            al_get_keyboard_state(&key_state);

            // Déplacer le carré avec les touches fléchées
            if (al_key_down(&key_state, ALLEGRO_KEY_UP) && y >= speed) {
                y -= speed;
            }
            if (al_key_down(&key_state, ALLEGRO_KEY_DOWN) && y <= SCREEN_HEIGHT - SQUARE_SIZE) {
                y += speed;
            }
            if (al_key_down(&key_state, ALLEGRO_KEY_LEFT) && x >= speed) {
                x -= speed;
            }
            if (al_key_down(&key_state, ALLEGRO_KEY_RIGHT) && x <= SCREEN_WIDTH - SQUARE_SIZE) {
                x += speed;
            }
            redraw = true;
        }

        // Si un redraw est nécessaire (lorsque le timer déclenche un événement)
        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;

            // Efface l'écran en noir
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // Dessine un carré blanc
            al_draw_filled_rectangle(x, y, x + SQUARE_SIZE, y + SQUARE_SIZE, al_map_rgb(255, 255, 255));

            // Met à jour l'affichage
            al_flip_display();
        }
    }

    // Nettoyage : libère les ressources
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);

    return 0;
}
