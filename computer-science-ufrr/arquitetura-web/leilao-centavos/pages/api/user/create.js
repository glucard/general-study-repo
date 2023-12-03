import prisma from "../../../lib/prisma";

export default async function createUser(req, res) {
    
    const { name, email, cpf, password } = req.body;

    const result = await prisma.user.create({
        data: {
            name: name,
            email: email,
            cpf: cpf,
            remain_bids: 10,
            password: password,
            role: 'user'
        },
    });

    console.log(result);
    res.json(result);
}