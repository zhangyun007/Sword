from pymemcache.client.hash import HashClient

client = HashClient([
    ('127.0.0.1', 11211),
    ('127.0.0.1', 11212)
])
client.set('some_key', 'some value')
result = client.get('some_key')
