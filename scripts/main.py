from sqlalchemy import create_engine, Column, Integer, String, Sequence
from sqlalchemy.orm import declarative_base
from sqlalchemy.orm import sessionmaker

DATABASE_URL = "sqlite:///./test.db"

engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()

class User(Base):
    __tablename__ = "users"
    id = Column(Integer, Sequence('user_id_seq'), primary_key=True)
    name = Column(String(50))
    email = Column(String(50))

# Create the tables
Base.metadata.create_all(bind=engine)

def init_db():
    db = SessionLocal()
    db.add(User(name="John Doe", email="john@example.com"))
    db.commit()
    db.close()

if __name__ == "__main__":
    init_db()
