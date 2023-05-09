package valuables;

public interface Storable<T1> {
	
	public abstract void setMyContainer(T1 container);
	public abstract T1 getMyContainer();

}
