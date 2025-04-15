import struct
import socket

def write_binary_file(file_name, float_values):

    int_value = len(float_values)

    # Converti le premier nombre en Big Endian
    int_value = socket.htonl(int_value)

    with open(file_name, 'wb') as f:
        # Ecrire la taille de la liste (int)
        f.write(struct.pack('i', int_value))
        
        # Ecrire les valeurs de la liste (float)
        for value in float_values:
            f.write(struct.pack('f', value))

file_name = '../datas/reals.dat'
float_values = [2.5, 5.5, 7.9]

write_binary_file(file_name, float_values)

print('Fichier', file_name, 'créé avec succès')
