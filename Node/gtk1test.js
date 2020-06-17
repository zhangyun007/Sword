imports.gi.versions['Gtk'] = '3.0';
const Gtk = imports.gi.Gtk;

// Create a new application
let app = new Gtk.Application({ application_id: 'com.example.GtkApplication' });

// When the application is launched…
app.connect('activate', () => {
    // … create a new window …
    let win = new Gtk.ApplicationWindow({ application: app });
    // … with a button in it …
    let btn = new Gtk.Button({ label: 'Hello, World!' });
    // … which closes the window when clicked
    btn.connect('clicked', () => { win.destroy(); });
    win.add(btn);
    win.show_all();
});