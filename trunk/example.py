import rc4

key = rc4.generate_key('12345')   #generate secret key
encrypted = rc4.encrypt(key, 'Hello world')   #encrypt with key
decrypted = rc4.decrypt(key, encrypted)   #decrypt with key
rc4.destroy_key(key)

print decrypted


