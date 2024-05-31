/*
3. Sea T una tabla de hash de tamaño 10 y h la siguiente función de hash h(k) = 4 + 3k
mod 10. Se quieren insertar en T elementos con claves (22, 23, 25, 15, 32, 18, 12, 19,
41, 31) en ese mismo orden usando h.

c. ¿Considera usted que la tabla T equipada con la función de hash h es buena
como tabla de hash? Justifique claramente su respuesta con respecto a las
condiciones que una función de hash debiese cumplir.

RESPUESTA:  No  me parece que la tabla T respecto de su funcion h(k) = 4 + 3k mod 10 sea buena como tabla hash,
            ya que durante el proceso de insercion hubo mas del 30% de claves sinonimas, que colisionan.

*/